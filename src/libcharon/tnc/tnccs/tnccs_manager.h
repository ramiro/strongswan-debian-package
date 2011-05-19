/*
 * Copyright (C) 2010 Andreas Steffen
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

/**
 * @defgroup tnccs_manager tnccs_manager
 * @{ @ingroup tnccs
 */

#ifndef TNCCS_MANAGER_H_
#define TNCCS_MANAGER_H_

#include "tnccs.h"

#include <tnc/imv/imv_recommendations.h>

typedef struct tnccs_manager_t tnccs_manager_t;

/**
 * The TNCCS manager manages all TNCCS implementations and creates instances.
 *
 * A plugin registers its implemented TNCCS protocol with the manager by
 * providing type and a constructor function. The manager then creates
 * TNCCS protocol instances via the provided constructor.
 */
struct tnccs_manager_t {

	/**
	 * Register a TNCCS protocol implementation.
	 *
	 * @param type			TNCCS protocol type
	 * @param constructor	constructor, returns a TNCCS protocol implementation
	 */
	void (*add_method)(tnccs_manager_t *this, tnccs_type_t type,
					   tnccs_constructor_t constructor);

	/**
	 * Unregister a TNCCS protocol implementation using it's constructor.
	 *
	 * @param constructor	constructor function to remove, as added in add_method
	 */
	void (*remove_method)(tnccs_manager_t *this, tnccs_constructor_t constructor);

	/**
	 * Create a new TNCCS protocol instance.
	 *
	 * @param type		  type of the TNCCS protocol
	 * @param is_server	  TRUE if TNC Server, FALSE if TNC Client
	 * @return			  TNCCS protocol instance, NULL if no constructor found
	 */
	tnccs_t* (*create_instance)(tnccs_manager_t *this, tnccs_type_t type,
								bool is_server);

	/**
	 * Create a TNCCS connection and assign a unique connection ID as well a
	 * callback function for adding a message to a TNCCS batch and create
	 * an empty set for collecting IMV recommendations
	 *
	 * @param tnccs						TNCCS connection instance
	 * @param send_message				TNCCS callback function
	 * @param request_handshake_retry	pointer to boolean variable
	 * @param recs						pointer to IMV recommendation set
	 * @return							assigned connection ID
	 */
	TNC_ConnectionID (*create_connection)(tnccs_manager_t *this, tnccs_t *tnccs,
										  tnccs_send_message_t send_message,
										  bool *request_handshake_retry,
						 				  recommendations_t **recs);

	/**
	 * Remove a TNCCS connection using its connection ID.
	 *
	 * @param id				ID of the connection to be removed
	 * @param is_server			TNC Server if TRUE, TNC Client if FALSE
	 */
	void (*remove_connection)(tnccs_manager_t *this, TNC_ConnectionID id,
							  bool is_server);

	/**
	 * Request a handshake retry
	 *
	 * @param is_imc			TRUE if IMC, FALSE if IMV
	 * @param imcv_id			ID of IMC or IMV requesting the retry
	 * @param id				ID of a specific connection or any connection
	 * @param reason			reason for the handshake retry
	 * @return					return code
	 */
	TNC_Result (*request_handshake_retry)(tnccs_manager_t *this, bool is_imc,
										  TNC_UInt32 imcv_id,
										  TNC_ConnectionID id,
										  TNC_RetryReason reason);

	/**
	 * Add an IMC/IMV message to the batch of a given connection ID.
	 *
	 * @param imc_id			ID of IMC or TNC_IMCID_ANY
	 * @param imv_id			ID of IMV or TNC_IMVID_ANY
	 * @param id				ID of target connection
	 * @param msg				message to be added
	 * @param msg_len			message length
	 * @param msg_type			message type
	 * @return					return code
	 */
	TNC_Result (*send_message)(tnccs_manager_t *this, TNC_IMCID imc_id,
													  TNC_IMVID imv_id,
													  TNC_ConnectionID id,
													  TNC_BufferReference msg,
													  TNC_UInt32 msg_len,
													  TNC_MessageType msg_type);

	/**
	 * Deliver an IMV Action Recommendation and IMV Evaluation Result to the TNCS
	 *
	 * @param imv_id			ID of the IMV providing the recommendation
	 * @param id				ID of target connection
	 * @param rec				action recommendation
	 * @param eval				evaluation result
	 * @return					return code
	 */
	TNC_Result (*provide_recommendation)(tnccs_manager_t *this,
										 TNC_IMVID imv_id,
										 TNC_ConnectionID id,
										 TNC_IMV_Action_Recommendation rec,
										 TNC_IMV_Evaluation_Result eval);

	/**
	 * Get the value of an attribute associated with a connection or with the
	 * TNCS as a whole.
	 *
	 * @param imv_id			ID of the IMV requesting the attribute
	 * @param id				ID of target connection
	 * @param attribute_id		ID of the requested attribute
	 * @param buffer_len		length of the buffer in bytes
	 * @param buffer			pointer to the buffer
	 * @param out_value_len		actual length of the returned attribute
	 * @return					return code
	 */
	TNC_Result (*get_attribute)(tnccs_manager_t *this,
							   TNC_IMVID imv_id,
							   TNC_ConnectionID id,
							   TNC_AttributeID attribute_id,
							   TNC_UInt32 buffer_len,
							   TNC_BufferReference buffer,
							   TNC_UInt32 *out_value_len);

	/**
	 * Set the value of an attribute associated with a connection or with the
	 * TNCS as a whole.
	 *
	 * @param imv_id			ID of the IMV setting the attribute
	 * @param id				ID of target connection
	 * @param attribute_id		ID of the attribute to be set
	 * @param buffer_len		length of the buffer in bytes
	 * @param buffer			pointer to the buffer
	 * @return					return code
	 */
	TNC_Result (*set_attribute)(tnccs_manager_t *this,
								TNC_IMVID imv_id,
								TNC_ConnectionID id,
								TNC_AttributeID attribute_id,
								TNC_UInt32 buffer_len,
								TNC_BufferReference buffer);

	/**
	 * Destroy a tnccs_manager instance.
	 */
	void (*destroy)(tnccs_manager_t *this);
};

/**
 * Create a tnccs_manager instance.
 */
tnccs_manager_t *tnccs_manager_create();

#endif /** TNCCS_MANAGER_H_ @}*/
