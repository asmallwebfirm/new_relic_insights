# New Relic: Rubicon

This module integrates Drupal with New Relic's Project Rubicon in a number of
ways described below.

### Watchdog Integration

Watchdog integration can be configured at the main configuration page for this
module. Watchdog integration is achieved by queueing messages logged to watchdog
in the Drupal Queue. Queued messages are processed automatically on cron, but
can also be processed manually in the following ways:

* If the [Drush Queue][] extension is installed, you can run
  ``` drush queue-run new_relic_rubicon ```
* You can also make a manual HTTP request to the following callback. When you do
  so, ensure your actual cron key is appended:
  ``` http://example.com/new-relic-rubicon-runner/your-cron-key-here```

You may wish to manually trigger queued events in one of the aforementioned ways
if you require real-time or near-real-time watchdog analysis.

When the queue is processed, events are sent through New Relic's Insert API as
events of type "watchdog."

The following fields are added to all watchdog events in Rubicon:

* __type__: The type of watchdog message being logged (often the module
  responsible for generating the message).
* __user__: The e-mail address of the user for whom the watchdog event was
  logged. For anonymous users, this field will be blank.
* __uid__: The user ID of the user for whom the watchdog event was logged. For
  anonymous users, the value of this field would be 0.
* __request_uri__: The request URI associated with the given watchdog event.
* __referer__: The URI associated with the referring page prior to this request.
* __ip__: The IP address from where the request for this page came.
* __timestamp__: The UNIX timestamp of the date/time the event occurred.
* __severity__: An integer representing the severity of this message (e.g. an
  alert vs. a notice vs. a warning vs. an emergency, see below for details).
* __fullMessage__: The fully processed message that you would normally see when
  analyzing watchdog messages and other notices/ errors.
* __message__: The raw, unprocessed message as it was passed to watchdog in
  code. This may include replacement tokens.

The following fields are optional and may or may not be passed along with events
in Rubicon:

* __links__: If a link/operation is associated with this watchdog event, it will
  be included here as a full HTML anchor.
* Variables: Some messages may include tokenized variables that are added when
  processing the associated message. The names and contents of these variables
  vary widely depending on the watchdog event being logged, but each token is
  included as a separate field/column in Rubicon. The name used for the field is
  the name of the token, prefixed with "_var_." For instance, in the following
  raw message, the subsequent tokenized variables would be included:
  ``` The node with nid %nid was edited by user with id !uid ```
    * _var_nid: Would contain the associated node ID.
    * _var_uid: Would contain the associated user ID.

Note that queueing of watchdog events for inserting into Rubicon does not
interfere with the core dblog or syslog modules. It may be used in tandem with
or independently of the aforementioned modules, depending on your use-case.

Note that there is currently no facility for reading back watchdog events once
they are in Rubicon.

### Accesslog Integration

Accesslog integration can be configured at the main configuration page for this
module. Accesslog integration depends on the [Better Statistics][] module.
Integration is achieved by decorating the preexisting transaction with custom
attributes provided by the core statistics module, as well as Better Statistics
API implementers.

The following fields are added to all transactions in rubicon

* __title__: Page Title for the given transaction
* __path__: Internal Drupal path for the given request, e.g. node/1
* __url__: The http referer for the given transaction
* __hostname__: The end-user's IP address for the given transaction
* __uid__: The Drupal user ID for the given transaction
* __sid__: The PHP Session ID for the given transaction
* __timer__: The length of time, in seconds, the given transaction took to
  generate from Drupal's perspective, probably redundant in the context of a New
  Relic Transaction.
* __timestamp__: The unix timestamp for the given transaction, also redundant in
the context of a New Relic Transaction.

The following fields, provided by Better Statistics can optionally be enabled in
the Better Statistics config area. Any other fields provided by contributed
modules are also available there.
* __user_agent__: The full user-agent string for the given transaction, a bit
  redundant but at least more verbose than what is provided by Rubicon.
* __peak_memory__: The peak memory, in bytes, used by PHP for the given
  transaction.
* __cache__: Drupal page cache hit/miss stat for the given transaction (one of:
  hit, miss, or null for uncacheable requests).

Note that transaction decoration with these custom attributes does not interfere
with the core Statistics or Better Statistics modules. It may be used in tandem
with or independently of the aforementioned modules, depending on your use-case.

Note that there is currently no facility for reading back accesslog metadata via
transactions once they are in Rubicon.

[drush queue]: https://drupal.org/project/drush_queue
[better statistics]: https://drupal.org/project/better_statistics
