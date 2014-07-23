<?php

/**
 * @file
 * Admin hooks and functions for the New Relic Insights module.
 */


/**
 * Primary settings form callback.
 */
function new_relic_insights_settings($form_state) {
  $form = array();

  // New Relic account ID.
  $form['new_relic_insights_account_id'] = array(
    '#type' => 'textfield',
    '#title' => t('New Relic account ID'),
    '#description' => t('Theaccount number associated with your Insights account.'),
    '#default_value' => variable_get('new_relic_insights_account_id', ''),
    '#required' => TRUE,
  );

  // Insert API Key
  $form['new_relic_insights_insert_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Insert API Key'),
    '#description' => t('An Insert Key generated for your Insights account.'),
    '#required' => TRUE,
    '#default_value' => variable_get('new_relic_insights_insert_key', ''),
  );

  // Query Key
  $form['new_relic_insights_query_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Query Key'),
    '#description' => t('A query key generated for your Insights account. This is required in order to query Insights.'),
    '#required' => FALSE,
    '#default_value' => variable_get('new_relic_insights_query_key', ''),
  );

  // Configurable expiry time.
  $expiry_times = drupal_map_assoc(array(0, 60, 300, 900, 3600, 10800, 21600, 43200, 86400, 604800, 2592000), 'format_interval');
  $expiry_times[0] = '<' . t('never') . '>';
  $form['new_relic_insights_expiry_time'] = array(
    '#type' => 'select',
    '#title' => t('Insights query data expiry time'),
    '#description' => t('Insights are queried and stored locally to speed up query response; depending on the number and size of objects returned, this can cause bloat. Set this to regularly purge locally cached Insight results after a given interval.'),
    '#required' => FALSE,
    '#options' => $expiry_times,
    '#default_value' => variable_get('new_relic_insights_expiry_time', 0),
    '#states' => array(
      'visible' => array(
        ':input[name="new_relic_insights_query_key"]' => array(
          'filled' => TRUE,
        ),
      ),
    ),
  );

  // Watchdog integration
  $form['new_relic_insights_collect_watchdog'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable watchdog integration'),
    '#default_value' => variable_get('new_relic_insights_collect_watchdog', FALSE)
  );

  // Accesslog integration (requires Better Statistics module).
  if (module_exists('better_statistics')) {
    $form['new_relic_insights_collect_accesslog'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable accesslog integration'),
      '#default_value' => variable_get('new_relic_insights_collect_accesslog', FALSE)
    );
  }

  return system_settings_form($form);
}

/**
 * Adds an "enable database logging" checkbox to the statistics config page.
 *
 * @see new_relic_insights_form_statistics_settings_form_alter()
 */
function _new_relic_insights_form_statistics_settings_form_alter(&$form, &$form_state) {
  // Give the option to disable database logging.
  $form['access']['statistics_log_to_db'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable database logging'),
    '#description' => t('Uncheck this to log access statistics only via New Relic Insights.'),
    '#default_value' => variable_get('statistics_log_to_db', TRUE),
  );

  // If database logging is disabled, we don't care about access log flushing.
  $form['access']['statistics_flush_accesslog_timer']['#states'] = array(
    'visible' => array(
      ':input[name="statistics_log_to_db"]' => array('checked' => TRUE),
    ),
  );
}
