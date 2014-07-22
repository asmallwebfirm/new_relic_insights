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
