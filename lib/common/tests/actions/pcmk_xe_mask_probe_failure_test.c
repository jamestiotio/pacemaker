/*
 * Copyright 2021-2024 the Pacemaker project contributors
 *
 * The version control history for this file may have further details.
 *
 * This source code is licensed under the GNU General Public License version 2
 * or later (GPLv2+) WITHOUT ANY WARRANTY.
 */

#include <crm_internal.h>

#include <crm/common/unittest_internal.h>

static void
op_is_not_probe_test(void **state) {
    xmlNode *node = NULL;

    /* Not worth testing this thoroughly since it's just a duplicate of whether
     * pcmk_op_is_probe works or not.
     */

    node = string2xml("<" PCMK__XE_LRM_RSC_OP " "
                          PCMK_XA_OPERATION "=\"" PCMK_ACTION_START "\" "
                          PCMK_META_INTERVAL "=\"0\"/>");
    assert_false(pcmk_xe_mask_probe_failure(node));
    free_xml(node);
}

static void
op_does_not_have_right_values_test(void **state) {
    xmlNode *node = NULL;
    char *s = NULL;

    node = string2xml("<" PCMK__XE_LRM_RSC_OP " "
                          PCMK_XA_OPERATION "=\"" PCMK_ACTION_MONITOR "\" "
                          PCMK_META_INTERVAL "=\"0\"/>");
    assert_false(pcmk_xe_mask_probe_failure(node));
    free_xml(node);

    s = crm_strdup_printf("<" PCMK__XE_LRM_RSC_OP " "
                              PCMK_XA_OPERATION "=\"" PCMK_ACTION_MONITOR "\" "
                              PCMK_META_INTERVAL "=\"0\" "
                              PCMK__XA_RC_CODE "=\"%d\" "
                              PCMK__XA_OP_STATUS "=\"\"/>",
                          PCMK_OCF_OK);
    node = string2xml(s);
    assert_false(pcmk_xe_mask_probe_failure(node));
    free(s);
    free_xml(node);
}

static void
check_values_test(void **state) {
    xmlNode *node = NULL;
    char *s = NULL;

    /* PCMK_EXEC_NOT_SUPPORTED */
    s = crm_strdup_printf("<" PCMK__XE_LRM_RSC_OP " "
                              PCMK_XA_OPERATION "=\"" PCMK_ACTION_MONITOR "\" "
                              PCMK_META_INTERVAL "=\"0\" "
                              PCMK__XA_RC_CODE "=\"%d\" "
                              PCMK__XA_OP_STATUS "=\"%d\"/>",
                          PCMK_OCF_OK, PCMK_EXEC_NOT_SUPPORTED);
    node = string2xml(s);
    assert_false(pcmk_xe_mask_probe_failure(node));
    free(s);
    free_xml(node);

    s = crm_strdup_printf("<" PCMK__XE_LRM_RSC_OP " "
                              PCMK_XA_OPERATION "=\"" PCMK_ACTION_MONITOR "\" "
                              PCMK_META_INTERVAL "=\"0\" "
                              PCMK__XA_RC_CODE "=\"%d\" "
                              PCMK__XA_OP_STATUS "=\"%d\"/>",
                          PCMK_OCF_NOT_INSTALLED, PCMK_EXEC_NOT_SUPPORTED);
    node = string2xml(s);
    assert_true(pcmk_xe_mask_probe_failure(node));
    free(s);
    free_xml(node);

    /* PCMK_EXEC_DONE */
    s = crm_strdup_printf("<" PCMK__XE_LRM_RSC_OP " "
                              PCMK_XA_OPERATION "=\"" PCMK_ACTION_MONITOR "\" "
                              PCMK_META_INTERVAL "=\"0\" "
                              PCMK__XA_RC_CODE "=\"%d\" "
                              PCMK__XA_OP_STATUS "=\"%d\"/>",
                          PCMK_OCF_OK, PCMK_EXEC_DONE);
    node = string2xml(s);
    assert_false(pcmk_xe_mask_probe_failure(node));
    free(s);
    free_xml(node);

    s = crm_strdup_printf("<" PCMK__XE_LRM_RSC_OP " "
                              PCMK_XA_OPERATION "=\"" PCMK_ACTION_MONITOR "\" "
                              PCMK_META_INTERVAL "=\"0\" "
                              PCMK__XA_RC_CODE "=\"%d\" "
                              PCMK__XA_OP_STATUS "=\"%d\"/>",
                          PCMK_OCF_INVALID_PARAM, PCMK_EXEC_DONE);
    node = string2xml(s);
    assert_true(pcmk_xe_mask_probe_failure(node));
    free(s);
    free_xml(node);

    s = crm_strdup_printf("<" PCMK__XE_LRM_RSC_OP " "
                              PCMK_XA_OPERATION "=\"" PCMK_ACTION_MONITOR "\" "
                              PCMK_META_INTERVAL "=\"0\" "
                              PCMK__XA_RC_CODE "=\"%d\" "
                              PCMK__XA_OP_STATUS "=\"%d\"/>",
                          PCMK_OCF_NOT_INSTALLED, PCMK_EXEC_DONE);
    node = string2xml(s);
    assert_true(pcmk_xe_mask_probe_failure(node));
    free(s);
    free_xml(node);

    s = crm_strdup_printf("<" PCMK__XE_LRM_RSC_OP " "
                              PCMK_XA_OPERATION "=\"" PCMK_ACTION_MONITOR "\" "
                              PCMK_META_INTERVAL "=\"0\" "
                              PCMK__XA_RC_CODE "=\"%d\" "
                              PCMK__XA_OP_STATUS "=\"%d\"/>",
                          PCMK_OCF_NOT_CONFIGURED, PCMK_EXEC_DONE);
    node = string2xml(s);
    assert_false(pcmk_xe_mask_probe_failure(node));
    free(s);
    free_xml(node);

    s = crm_strdup_printf("<" PCMK__XE_LRM_RSC_OP " "
                              PCMK_XA_OPERATION "=\"" PCMK_ACTION_MONITOR "\" "
                              PCMK_META_INTERVAL "=\"0\" "
                              PCMK__XA_RC_CODE "=\"%d\" "
                              PCMK__XA_OP_STATUS "=\"%d\"/>",
                          PCMK_OCF_NOT_RUNNING, PCMK_EXEC_DONE);
    node = string2xml(s);
    assert_false(pcmk_xe_mask_probe_failure(node));
    free(s);
    free_xml(node);

    /* PCMK_EXEC_NOT_INSTALLED */
    s = crm_strdup_printf("<" PCMK__XE_LRM_RSC_OP " "
                              PCMK_XA_OPERATION "=\"" PCMK_ACTION_MONITOR "\" "
                              PCMK_META_INTERVAL "=\"0\" "
                              PCMK__XA_RC_CODE "=\"%d\" "
                              PCMK__XA_OP_STATUS "=\"%d\"/>",
                          PCMK_OCF_OK, PCMK_EXEC_NOT_INSTALLED);
    node = string2xml(s);
    assert_true(pcmk_xe_mask_probe_failure(node));
    free(s);
    free_xml(node);

    s = crm_strdup_printf("<" PCMK__XE_LRM_RSC_OP " "
                              PCMK_XA_OPERATION "=\"" PCMK_ACTION_MONITOR "\" "
                              PCMK_META_INTERVAL "=\"0\" "
                              PCMK__XA_RC_CODE "=\"%d\" "
                              PCMK__XA_OP_STATUS "=\"%d\"/>",
                          PCMK_OCF_NOT_INSTALLED, PCMK_EXEC_NOT_INSTALLED);
    node = string2xml(s);
    assert_true(pcmk_xe_mask_probe_failure(node));
    free(s);
    free_xml(node);

    /* PCMK_EXEC_ERROR */
    s = crm_strdup_printf("<" PCMK__XE_LRM_RSC_OP " "
                              PCMK_XA_OPERATION "=\"" PCMK_ACTION_MONITOR "\" "
                              PCMK_META_INTERVAL "=\"0\" "
                              PCMK__XA_RC_CODE "=\"%d\" "
                              PCMK__XA_OP_STATUS "=\"%d\"/>",
                          PCMK_OCF_OK, PCMK_EXEC_ERROR);
    node = string2xml(s);
    assert_false(pcmk_xe_mask_probe_failure(node));
    free(s);
    free_xml(node);

    s = crm_strdup_printf("<" PCMK__XE_LRM_RSC_OP " "
                              PCMK_XA_OPERATION "=\"" PCMK_ACTION_MONITOR "\" "
                              PCMK_META_INTERVAL "=\"0\" "
                              PCMK__XA_RC_CODE "=\"%d\" "
                              PCMK__XA_OP_STATUS "=\"%d\"/>",
                          PCMK_OCF_INVALID_PARAM, PCMK_EXEC_ERROR);
    node = string2xml(s);
    assert_true(pcmk_xe_mask_probe_failure(node));
    free(s);
    free_xml(node);

    s = crm_strdup_printf("<" PCMK__XE_LRM_RSC_OP " "
                              PCMK_XA_OPERATION "=\"" PCMK_ACTION_MONITOR "\" "
                              PCMK_META_INTERVAL "=\"0\" "
                              PCMK__XA_RC_CODE "=\"%d\" "
                              PCMK__XA_OP_STATUS "=\"%d\"/>",
                          PCMK_OCF_NOT_INSTALLED, PCMK_EXEC_ERROR);
    node = string2xml(s);
    assert_true(pcmk_xe_mask_probe_failure(node));
    free(s);
    free_xml(node);

    s = crm_strdup_printf("<" PCMK__XE_LRM_RSC_OP " "
                              PCMK_XA_OPERATION "=\"" PCMK_ACTION_MONITOR "\" "
                              PCMK_META_INTERVAL "=\"0\" "
                              PCMK__XA_RC_CODE "=\"%d\" "
                              PCMK__XA_OP_STATUS "=\"%d\"/>",
                          PCMK_OCF_NOT_CONFIGURED, PCMK_EXEC_ERROR);
    node = string2xml(s);
    assert_false(pcmk_xe_mask_probe_failure(node));
    free(s);
    free_xml(node);

    s = crm_strdup_printf("<" PCMK__XE_LRM_RSC_OP " "
                              PCMK_XA_OPERATION "=\"" PCMK_ACTION_MONITOR "\" "
                              PCMK_META_INTERVAL "=\"0\" "
                              PCMK__XA_RC_CODE "=\"%d\" "
                              PCMK__XA_OP_STATUS "=\"%d\"/>",
                          PCMK_OCF_NOT_RUNNING, PCMK_EXEC_ERROR);
    node = string2xml(s);
    assert_false(pcmk_xe_mask_probe_failure(node));
    free(s);
    free_xml(node);

    /* PCMK_EXEC_ERROR_HARD */
    s = crm_strdup_printf("<" PCMK__XE_LRM_RSC_OP " "
                              PCMK_XA_OPERATION "=\"" PCMK_ACTION_MONITOR "\" "
                              PCMK_META_INTERVAL "=\"0\" "
                              PCMK__XA_RC_CODE "=\"%d\" "
                              PCMK__XA_OP_STATUS "=\"%d\"/>",
                          PCMK_OCF_OK, PCMK_EXEC_ERROR_HARD);
    node = string2xml(s);
    assert_false(pcmk_xe_mask_probe_failure(node));
    free(s);
    free_xml(node);

    s = crm_strdup_printf("<" PCMK__XE_LRM_RSC_OP " "
                              PCMK_XA_OPERATION "=\"" PCMK_ACTION_MONITOR "\" "
                              PCMK_META_INTERVAL "=\"0\" "
                              PCMK__XA_RC_CODE "=\"%d\" "
                              PCMK__XA_OP_STATUS "=\"%d\"/>",
                          PCMK_OCF_INVALID_PARAM, PCMK_EXEC_ERROR_HARD);
    node = string2xml(s);
    assert_true(pcmk_xe_mask_probe_failure(node));
    free(s);
    free_xml(node);

    s = crm_strdup_printf("<" PCMK__XE_LRM_RSC_OP " "
                              PCMK_XA_OPERATION "=\"" PCMK_ACTION_MONITOR "\" "
                              PCMK_META_INTERVAL "=\"0\" "
                              PCMK__XA_RC_CODE "=\"%d\" "
                              PCMK__XA_OP_STATUS "=\"%d\"/>",
                          PCMK_OCF_NOT_INSTALLED, PCMK_EXEC_ERROR_HARD);
    node = string2xml(s);
    assert_true(pcmk_xe_mask_probe_failure(node));
    free(s);
    free_xml(node);

    s = crm_strdup_printf("<" PCMK__XE_LRM_RSC_OP " "
                              PCMK_XA_OPERATION "=\"" PCMK_ACTION_MONITOR "\" "
                              PCMK_META_INTERVAL "=\"0\" "
                              PCMK__XA_RC_CODE "=\"%d\" "
                              PCMK__XA_OP_STATUS "=\"%d\"/>",
                          PCMK_OCF_NOT_CONFIGURED, PCMK_EXEC_ERROR_HARD);
    node = string2xml(s);
    assert_false(pcmk_xe_mask_probe_failure(node));
    free(s);
    free_xml(node);

    s = crm_strdup_printf("<" PCMK__XE_LRM_RSC_OP " "
                              PCMK_XA_OPERATION "=\"" PCMK_ACTION_MONITOR "\" "
                              PCMK_META_INTERVAL "=\"0\" "
                              PCMK__XA_RC_CODE "=\"%d\" "
                              PCMK__XA_OP_STATUS "=\"%d\"/>",
                          PCMK_OCF_NOT_RUNNING, PCMK_EXEC_ERROR_HARD);
    node = string2xml(s);
    assert_false(pcmk_xe_mask_probe_failure(node));
    free(s);
    free_xml(node);

    /* PCMK_EXEC_ERROR_FATAL */
    s = crm_strdup_printf("<" PCMK__XE_LRM_RSC_OP " "
                              PCMK_XA_OPERATION "=\"" PCMK_ACTION_MONITOR "\" "
                              PCMK_META_INTERVAL "=\"0\" "
                              PCMK__XA_RC_CODE "=\"%d\" "
                              PCMK__XA_OP_STATUS "=\"%d\"/>",
                          PCMK_OCF_OK, PCMK_EXEC_ERROR_FATAL);
    node = string2xml(s);
    assert_false(pcmk_xe_mask_probe_failure(node));
    free(s);
    free_xml(node);

    s = crm_strdup_printf("<" PCMK__XE_LRM_RSC_OP " "
                              PCMK_XA_OPERATION "=\"" PCMK_ACTION_MONITOR "\" "
                              PCMK_META_INTERVAL "=\"0\" "
                              PCMK__XA_RC_CODE "=\"%d\" "
                              PCMK__XA_OP_STATUS "=\"%d\"/>",
                          PCMK_OCF_INVALID_PARAM, PCMK_EXEC_ERROR_FATAL);
    node = string2xml(s);
    assert_true(pcmk_xe_mask_probe_failure(node));
    free(s);
    free_xml(node);

    s = crm_strdup_printf("<" PCMK__XE_LRM_RSC_OP " "
                              PCMK_XA_OPERATION "=\"" PCMK_ACTION_MONITOR "\" "
                              PCMK_META_INTERVAL "=\"0\" "
                              PCMK__XA_RC_CODE "=\"%d\" "
                              PCMK__XA_OP_STATUS "=\"%d\"/>",
                          PCMK_OCF_NOT_INSTALLED, PCMK_EXEC_ERROR_FATAL);
    node = string2xml(s);
    assert_true(pcmk_xe_mask_probe_failure(node));
    free(s);
    free_xml(node);

    s = crm_strdup_printf("<" PCMK__XE_LRM_RSC_OP " "
                              PCMK_XA_OPERATION "=\"" PCMK_ACTION_MONITOR "\" "
                              PCMK_META_INTERVAL "=\"0\" "
                              PCMK__XA_RC_CODE "=\"%d\" "
                              PCMK__XA_OP_STATUS "=\"%d\"/>",
                          PCMK_OCF_NOT_CONFIGURED, PCMK_EXEC_ERROR_FATAL);
    node = string2xml(s);
    assert_false(pcmk_xe_mask_probe_failure(node));
    free(s);
    free_xml(node);

    s = crm_strdup_printf("<" PCMK__XE_LRM_RSC_OP " "
                              PCMK_XA_OPERATION "=\"" PCMK_ACTION_MONITOR "\" "
                              PCMK_META_INTERVAL "=\"0\" "
                              PCMK__XA_RC_CODE "=\"%d\" "
                              PCMK__XA_OP_STATUS "=\"%d\"/>",
                          PCMK_OCF_NOT_RUNNING, PCMK_EXEC_ERROR_FATAL);
    node = string2xml(s);
    assert_false(pcmk_xe_mask_probe_failure(node));
    free(s);
    free_xml(node);
}

PCMK__UNIT_TEST(NULL, NULL,
                cmocka_unit_test(op_is_not_probe_test),
                cmocka_unit_test(op_does_not_have_right_values_test),
                cmocka_unit_test(check_values_test))
