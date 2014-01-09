<?php

/**
 * @file
 * Admin hooks and functions for the New Relic: Rubicon module.
 */


/**
 * Primary settings form callback.
 */
function new_relic_rubicon_settings($form_state) {
  $form = array();

  // New Relic account ID.
  $form['new_relic_rubicon_account_id'] = array(
    '#type' => 'textfield',
    '#title' => t('New Relic Account ID'),
    '#description' => t('The New Relic account number associated with your desired Rubicon instance.'),
    '#default_value' => variable_get('new_relic_rubicon_account_id', ''),
    '#required' => TRUE,
  );

  // Insert API Key
  $form['new_relic_rubicon_insert_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Insert API Key'),
    '#description' => t('The Insert Key generated for your Rubicon instance.'),
    '#required' => TRUE,
    '#default_value' => variable_get('new_relic_rubicon_insert_key', ''),
  );

  // Watchdog integration
  $form['new_relic_rubicon_collect_watchdog'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable watchdog integration'),
    '#default_value' => variable_get('new_relic_rubicon_collect_watchdog', FALSE)
  );

  // Accesslog integration (requires Better Statistics module).
  if (module_exists('better_statistics')) {
    $form['new_relic_rubicon_collect_accesslog'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable accesslog integration'),
      '#default_value' => variable_get('new_relic_rubicon_collect_accesslog', FALSE)
    );
  }

  return system_settings_form($form);
}
