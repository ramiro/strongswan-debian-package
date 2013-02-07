/*
 * Copyright (C) 2011 Sansar Choinyambuu
 * HSR Hochschule fuer Technik Rapperswil
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

#include "pts_file_meas.h"

#include <collections/linked_list.h>
#include <utils/debug.h>

#include <sys/stat.h>
#include <libgen.h>
#include <errno.h>

typedef struct private_pts_file_meas_t private_pts_file_meas_t;

/**
 * Private data of a pts_file_meas_t object.
 *
 */
struct private_pts_file_meas_t {

	/**
	 * Public pts_file_meas_t interface.
	 */
	pts_file_meas_t public;

	/**
	 * ID of PTS File Measurement Request
	 */
	u_int16_t request_id;

	/**
	 * List of File Measurements
	 */
	linked_list_t *list;
};

typedef struct entry_t entry_t;

/**
 * PTS File Measurement entry
 */
struct entry_t {
	char	 *filename;
	chunk_t  measurement;
};

/**
 * Free an entry_t object
 */
static void free_entry(entry_t *entry)
{
	if (entry)
	{
		free(entry->filename);
		free(entry->measurement.ptr);
		free(entry);
	}
}

METHOD(pts_file_meas_t, get_request_id, u_int16_t,
	private_pts_file_meas_t *this)
{
	return this->request_id;
}

METHOD(pts_file_meas_t, get_file_count, int,
	private_pts_file_meas_t *this)
{
	return this->list->get_count(this->list);
}

METHOD(pts_file_meas_t, add, void,
	private_pts_file_meas_t *this, char *filename, chunk_t measurement)
{
	entry_t *entry;

	entry = malloc_thing(entry_t);
	entry->filename = strdup(filename);
	entry->measurement = chunk_clone(measurement);

	this->list->insert_last(this->list, entry);
}

/**
 * Enumerate file measurement entries
 */
static bool entry_filter(void *null, entry_t **entry, char **filename,
						 void *i2, chunk_t *measurement)
{
	*filename = (*entry)->filename;
	*measurement = (*entry)->measurement;
	return TRUE;
}

METHOD(pts_file_meas_t, create_enumerator, enumerator_t*,
	private_pts_file_meas_t *this)
{
	return enumerator_create_filter(this->list->create_enumerator(this->list),
								   (void*)entry_filter, NULL, NULL);
}

METHOD(pts_file_meas_t, check, bool,
	private_pts_file_meas_t *this, pts_database_t *pts_db, char *product,
	pts_meas_algorithms_t algo)
{
	enumerator_t *enumerator;
	entry_t *entry;
	int count_ok = 0, count_not_found = 0, count_differ = 0;
	status_t status;

	enumerator = this->list->create_enumerator(this->list);
	while (enumerator->enumerate(enumerator, &entry))
	{
		status = pts_db->check_file_measurement(pts_db, product, algo,
									entry->measurement, entry->filename);
		switch (status)
		{
			case SUCCESS:
				DBG3(DBG_PTS, "  %#B for '%s' is ok", &entry->measurement,
													   entry->filename);
				count_ok++;
				break;
			case NOT_FOUND:
				DBG2(DBG_PTS, "  %#B for '%s' not found", &entry->measurement,
														   entry->filename);
				count_not_found++;
				break;
			case VERIFY_ERROR:
				DBG1(DBG_PTS, "  %#B for '%s' differs", &entry->measurement,
														 entry->filename);
				count_differ++;
				break;
			case FAILED:
			default:
				DBG1(DBG_PTS, "  %#B for '%s' failed", &entry->measurement,
														entry->filename);
		}
	}
	enumerator->destroy(enumerator);

	DBG1(DBG_PTS, "%d measurements, %d ok, %d not found, %d differ",
		 this->list->get_count(this->list),
		 count_ok, count_not_found, count_differ);
	return TRUE;
}

METHOD(pts_file_meas_t, verify, bool,
	private_pts_file_meas_t *this, enumerator_t *e_hash, bool is_dir)
{
	char *filename;
	chunk_t measurement;
	entry_t *entry;
	enumerator_t *enumerator;
	bool found, success = TRUE;

	while (e_hash->enumerate(e_hash, &filename, &measurement))
	{
		found = FALSE;

		enumerator = this->list->create_enumerator(this->list);
		while (enumerator->enumerate(enumerator, &entry))
		{
			if (!is_dir || streq(filename, entry->filename))
			{
				found = TRUE;
				break;
			}
		}
		enumerator->destroy(enumerator);

		if (!found)
		{
			DBG1(DBG_PTS, "  no measurement found for '%s'", filename);
			success = FALSE;
			continue;
		}
		if (chunk_equals(measurement, entry->measurement))
		{
			DBG2(DBG_PTS, "  %#B for '%s' is ok", &measurement, filename);
		}
		else
		{
			DBG1(DBG_PTS, "  %#B for '%s' is incorrect", &measurement, filename);
			success = FALSE;
		}
		if (!is_dir)
		{
			break;
		}
	}
	return success;
}

METHOD(pts_file_meas_t, destroy, void,
	private_pts_file_meas_t *this)
{
	this->list->destroy_function(this->list, (void *)free_entry);
	free(this);
}

/**
 * See header
 */
pts_file_meas_t *pts_file_meas_create(u_int16_t request_id)
{
	private_pts_file_meas_t *this;

	INIT(this,
		.public = {
			.get_request_id = _get_request_id,
			.get_file_count = _get_file_count,
			.add = _add,
			.create_enumerator = _create_enumerator,
			.check = _check,
			.verify = _verify,
			.destroy = _destroy,
		},
		.request_id = request_id,
		.list = linked_list_create(),
	);

	return &this->public;
}

/**
 * Hash a file with a given absolute pathname
 */
static bool hash_file(hasher_t *hasher, char *pathname, u_char *hash)
{
	u_char buffer[4096];
	size_t bytes_read;
	bool success = TRUE;
	FILE *file;

	file = fopen(pathname, "rb");
	if (!file)
	{
		DBG1(DBG_PTS,"  file '%s' can not be opened, %s", pathname,
			 strerror(errno));
		return FALSE;
	}
	while (TRUE)
	{
		bytes_read = fread(buffer, 1, sizeof(buffer), file);
		if (bytes_read > 0)
		{
			if (!hasher->get_hash(hasher, chunk_create(buffer, bytes_read), NULL))
			{
				DBG1(DBG_PTS, "  hasher increment error");
				success = FALSE;
				break;
			}
		}
		else
		{
			if (!hasher->get_hash(hasher, chunk_empty, hash))
			{
				DBG1(DBG_PTS, "  hasher finalize error");
				success = FALSE;
			}
			break;
		}
	}
	fclose(file);

	return success;
}

/**
 * See header
 */
pts_file_meas_t *pts_file_meas_create_from_path(u_int16_t request_id,
							char *pathname, bool is_dir, bool use_rel_name,
							pts_meas_algorithms_t alg)
{
	private_pts_file_meas_t *this;
	hash_algorithm_t hash_alg;
	hasher_t *hasher;
	u_char hash[HASH_SIZE_SHA384];
	chunk_t measurement;
	char* filename;
	bool success = TRUE;

	/* Create a hasher and a hash measurement buffer */
	hash_alg = pts_meas_algo_to_hash(alg);
	hasher = lib->crypto->create_hasher(lib->crypto, hash_alg);
	if (!hasher)
	{
		DBG1(DBG_PTS, "hasher %N not available", hash_algorithm_names, hash_alg);
		return NULL;
	}
	measurement = chunk_create(hash, hasher->get_hash_size(hasher));

	INIT(this,
		.public = {
			.get_request_id = _get_request_id,
			.get_file_count = _get_file_count,
			.add = _add,
			.create_enumerator = _create_enumerator,
			.check = _check,
			.verify = _verify,
			.destroy = _destroy,
		},
		.request_id = request_id,
		.list = linked_list_create(),
	);

	if (is_dir)
	{
		enumerator_t *enumerator;
		char *rel_name, *abs_name;
		struct stat st;

		enumerator = enumerator_create_directory(pathname);
		if (!enumerator)
		{
			DBG1(DBG_PTS, "  directory '%s' can not be opened, %s", pathname,
				 strerror(errno));
			success = FALSE;
			goto end;
		}
		while (enumerator->enumerate(enumerator, &rel_name, &abs_name, &st))
		{
			/* measure regular files only */
			if (S_ISREG(st.st_mode) && *rel_name != '.')
			{
				if (!hash_file(hasher, abs_name, hash))
				{
					success = FALSE;
					break;
				}
				filename = use_rel_name ? rel_name : abs_name;
				DBG2(DBG_PTS, "  %#B for '%s'", &measurement, filename);
				add(this, filename, measurement);
			}
		}
		enumerator->destroy(enumerator);
	}
	else
	{
		if (!hash_file(hasher, pathname, hash))
		{
			success = FALSE;
			goto end;
		}
		filename = use_rel_name ? basename(pathname) : pathname;
		DBG2(DBG_PTS, "  %#B for '%s'", &measurement, filename);
		add(this, filename, measurement);
	}

end:
	hasher->destroy(hasher);
	if (success)
	{
		return &this->public;
	}
	else
	{
		destroy(this);
		return NULL;
	}
}
