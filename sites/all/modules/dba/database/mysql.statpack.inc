<?php

function dba_mysql_statpack_uptime($report) {
  $uptime = $report->Uptime;
  $days = (int)($uptime / 86400);
  $uptime %= 86400;

  $hours = (int)($uptime / 3600);
  $uptime %= 3600 ;

  $minutes = (int)($uptime / 60);

  $granularity = 0;
  $uptime = '';
  if ($days > 0 && $granularity < 2) {
    $uptime .= t('!days ', array('!days' => format_plural($days, '1 day', '@count days')));
    $granularity++;
  }
  if ($hours > 0 && $granularity < 2) {
    $uptime .= t('!hours ', array('!hours' => format_plural($hours, '1 hour', '@count hours')));
    $granularity++;
  }
  if ($minutes > 0 && $granularity < 2) {
    $uptime .= "$minutes mins ";
    $uptime .= t('!minutes ', array('!minutes' => format_plural($minutes, '1 min', '@count mins')));
    $granularity++;
  }
  return $uptime;
}

function dba_mysql_statpack_output($reports) {
  $output = array();

  $output[] = dba_statpack_center(t('Database Activity'));
  $output[] = dba_statpack_line();

  $output[] = dba_mysql_statpack_activity(t('Threads Connected'), $reports[0]->Threads_connected, $reports[1]->Threads_connected);
  $output[] = dba_mysql_statpack_activity(t('Threads Running'), $reports[0]->Threads_running, $reports[1]->Threads_running);
  $output[] = dba_mysql_statpack_activity(t('Questions'), $reports[0]->Questions, $reports[1]->Questions);
  $output[] = dba_mysql_statpack_activity(t('Bytes Received'), $reports[0]->Bytes_received, $reports[1]->Bytes_received, TRUE);
  $output[] = dba_mysql_statpack_activity(t('Bytes Sent'), $reports[0]->Bytes_sent, $reports[1]->Bytes_sent, TRUE);
  $output[] = dba_mysql_statpack_activity(t('Aborted Clients'), $reports[0]->Aborted_clients, $reports[1]->Aborted_clients);
  $output[] = dba_mysql_statpack_activity(t('Aborted Connects'), $reports[0]->Aborted_connects, $reports[1]->Aborted_connects);

  $output[] = dba_statpack_line();
  $output[] = dba_statpack_center(t('Statement Activity'));
  $output[] = dba_statpack_line();

  // Statement totals
  $statements = array();
  $statements[0] = $reports[0]->Com_select + $reports[0]->Com_insert + $reports[0]->Com_update + $reports[0]->Com_delete + $reports[0]->Com_replace + $reports[0]->Com_insert_select + $reports[0]->Com_replace_select + $reports[0]->Com_update_multi + $reports[0]->Com_delete_multi + $reports[0]->Com_commit + $reports[0]->Com_rollback;
  $statements[1] = $reports[1]->Com_select + $reports[1]->Com_insert + $reports[1]->Com_update + $reports[1]->Com_delete + $reports[1]->Com_replace + $reports[1]->Com_insert_select + $reports[1]->Com_replace_select + $reports[1]->Com_update_multi + $reports[1]->Com_delete_multi + $reports[1]->Com_commit + $reports[1]->Com_rollback;
  $statements[2] = $statements[1] - $statements[0];

  if ($return = dba_mysql_statpack_statement(t('SELECT'), $reports[0]->Com_select, $reports[1]->Com_select, $statements)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_statement(t('INSERT'), $reports[0]->Com_insert, $reports[1]->Com_insert, $statements)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_statement(t('UPDATE'), $reports[0]->Com_update, $reports[1]->Com_update, $statements)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_statement(t('DELETE'), $reports[0]->Com_delete, $reports[1]->Com_delete, $statements)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_statement(t('REPLACE'), $reports[0]->Com_replace, $reports[1]->Com_replace, $statements)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_statement(t('INSERT ... SELECT'), $reports[0]->Com_insert_select, $reports[1]->Com_insert_select, $statements)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_statement(t('REPLACE ... SELECT'), $reports[0]->Com_replace_select, $reports[1]->Com_replace_select, $statements)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_statement(t('Multi UPDATE'), $reports[0]->Com_update_multi, $reports[1]->Com_update_multi, $statements)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_statement(t('Multi DELETE'), $reports[0]->Com_delete_multi, $reports[1]->Com_delete_multi, $statements)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_statement(t('COMMIT'), $reports[0]->Com_commit, $reports[1]->Com_commit, $statements)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_statement(t('ROLLBACK'), $reports[0]->Com_rollback, $reports[1]->Com_rollback, $statements)) {
    $output[] = $return;
  }

  $output[] = dba_statpack_line();
  $output[] = dba_statpack_center(t('Admin Commands'));
  $output[] = dba_statpack_line();

  if ($return = dba_mysql_statpack_activity(t('KILL'), $reports[0]->Com_kill, $reports[1]->Com_kill, 0)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_activity(t('FLUSH'), $reports[0]->Com_flush, $reports[1]->Com_flush, 0)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_activity(t('ANALYZE TABLE'), $reports[0]->Com_analyze, $reports[1]->Com_analyze, 0)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_activity(t('OPTIMIZE TABLE'), $reports[0]->Com_optimize, $reports[1]->Com_optimize, 0)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_activity(t('CHECK TABLE'), $reports[0]->Com_check, $reports[1]->Com_check, 0)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_activity(t('REPAIR TABLE'), $reports[0]->Com_repair, $reports[1]->Com_repair, 0)) {
    $output[] = $return;
  }

  $output[] = dba_statpack_line();
  $output[] = dba_statpack_center(t('Thread Cache'));
  $output[] = dba_statpack_line();

  $output[] = dba_statpack_columns(array(t('Thread Efficiency'), '', '', dba_statpack_short(100 - dba_statpack_to_percentage($reports[1]->Threads_created / $reports[1]->Connections)) .'%')); 
  $output[] = dba_mysql_statpack_activity(t('Connections'), $reports[0]->Connections, $reports[1]->Connections);
  $output[] = dba_mysql_statpack_activity(t('Threads Created'), $reports[0]->Threads_created, $reports[1]->Threads_created);

  $output[] = dba_statpack_line();
  $output[] = dba_statpack_center(t('Table Cache'));
  $output[] = dba_statpack_line();

  $output[] = dba_statpack_columns(array(t('table_cache Efficiency'), '', '', dba_statpack_short(dba_statpack_to_percentage($reports[1]->Open_tables / ($reports[1]->Opened_tables + 1))) .'%')); 
  $output[] = dba_mysql_statpack_activity(t('Open Tables'), $reports[0]->Open_tables, $reports[1]->Open_tables);
  $output[] = dba_mysql_statpack_activity(t('Opened Tables'), $reports[0]->Opened_tables, $reports[1]->Opened_tables);

  $output[] = dba_statpack_line();
  $output[] = dba_statpack_center(t('MyISAM Key Cache'));
  $output[] = dba_statpack_line();

  $output[] = dba_statpack_columns(array(t('Cache Read Efficiency'), '', '', dba_statpack_short(dba_statpack_to_percentage($reports[1]->Key_reads / ($reports[1]->Key_read_requests + 1))) .'%')); 
  $output[] = dba_statpack_columns(array(t('Cache Write Efficiency'), '', '', dba_statpack_short(dba_statpack_to_percentage($reports[1]->Key_writes / ($reports[1]->Key_write_requests + 1))) .'%')); 
  if ($return = dba_mysql_statpack_format(t('Memory Used'), $reports[1]->Key_blocks_used - $reports[0]->Key_blocks_used, '', $reports[1]->Key_blocks_used, TRUE)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_format(t('Memory Free'), $reports[1]->Key_blocks_unused - $reports[0]->Key_blocks_unused, '', $reports[1]->Key_blocks_unused, TRUE)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_activity(t('Key Reads'), $reports[1]->Key_reads, $reports[1]->Key_reads)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_activity(t('Key Read Requests'), $reports[1]->Key_read_requests, $reports[1]->Key_read_requests)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_activity(t('Key Writes'), $reports[1]->Key_writes, $reports[1]->Key_writes)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_activity(t('Key Write Requests'), $reports[1]->Key_write_requests, $reports[1]->Key_write_requests)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_activity(t('Blocks Not Flushed'), $reports[1]->Key_blocks_not_flushed, $reports[0]->Key_blocks_not_flushed)) {
    $output[] = $return;
  }

  $output[] = dba_statpack_line();
  $output[] = dba_statpack_center(t('InnoDB Buffer Pool'));
  $output[] = dba_statpack_line();

  $output[] = dba_statpack_columns(array(t('Buffer Pool Read Efficiency'), '', '', dba_statpack_short(100 - dba_statpack_to_percentage($reports[1]->Innodb_buffer_pool_reads / ($reports[1]->Innodb_buffer_pool_read_requests + 1))) .'%')); 
  if ($return = dba_mysql_statpack_format(t('Memory Total'), ($reports[1]->Innodb_buffer_pool_pages_total - $reports[0]->Innodb_buffer_pool_pages_total) * 16384, '', $reports[1]->Innodb_buffer_pool_pages_total * 16384, TRUE)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_format(t('Memory Free'), ($reports[1]->Innodb_buffer_pool_pages_free - $reports[0]->Innodb_buffer_pool_pages_free) * 16384, '', $reports[1]->Innodb_buffer_pool_pages_free * 16384, TRUE)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_format(t('Memory Data'), ($reports[1]->Innodb_buffer_pool_pages_data - $reports[0]->Innodb_buffer_pool_pages_data) * 16384, '', $reports[1]->Innodb_buffer_pool_pages_data * 16384, TRUE)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_format(t('Memory Dirty'), ($reports[1]->Innodb_buffer_pool_pages_dirty - $reports[0]->Innodb_buffer_pool_pages_dirty) * 16384, '', $reports[1]->Innodb_buffer_pool_pages_dirty * 16384, TRUE)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_format(t('Data Read'), ($reports[1]->Innodb_data_read - $reports[0]->Innodb_data_read) * 16384, '', $reports[1]->Innodb_data_read, TRUE)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_format(t('Data Written'), $reports[1]->Innodb_data_written - $reports[0]->Innodb_data_written, '', $reports[1]->Innodb_data_written, TRUE)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_activity(t('Buffer Pool Reads'), $reports[1]->Innodb_buffer_pool_reads, $reports[0]->Innodb_buffer_pool_reads)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_activity(t('Buffer Pool Read Requests'), $reports[0]->Innodb_buffer_pool_read_requests, $reports[1]->Innodb_buffer_pool_read_requests)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_activity(t('Buffer Pool Write Requests'), $reports[0]->Innodb_buffer_pool_write_requests, $reports[1]->Innodb_buffer_pool_write_requests)) {
    $output[] = $return;
  }

  $output[] = dba_statpack_line();
  $output[] = dba_statpack_center(t('InnoDB Log Files'));
  $output[] = dba_statpack_line();

  if ($return = dba_mysql_statpack_format(t('Log Data Written'), $reports[1]->Innodb_os_log_written - $reports[0]->Innodb_os_log_written, '', $reports[1]->Innodb_os_log_written, TRUE)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_activity(t('Log Writes'), $reports[0]->Innodb_log_writes, $reports[1]->Innodb_log_writes)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_activity(t('Log Write Requests'), $reports[0]->Innodb_log_write_requests, $reports[1]->Innodb_log_write_requests)) {
    $output[] = $return;
  }
  if ($return = dba_mysql_statpack_activity(t('Log Waits'), $reports[0]->Innodb_log_waits, $reports[1]->Innodb_log_waits)) {
    $output[] = $return;
  }

  $output[] = dba_statpack_line();
  $output[] = dba_statpack_center(t('Query Cache'));
  $output[] = dba_statpack_line();

  return $output;
}

function dba_mysql_statpack_activity($title, $first, $last, $bytes = FALSE) {
  $delta = $last - $first;
  $col2 = $delta / variable_get('dba_statpack_interval', DBA_STATPACK_INTERVAL);
  return dba_mysql_statpack_format($title, $delta, $col2, $last, $bytes);
}

function dba_mysql_statpack_format($title, $col1, $col2, $col3, $bytes = FALSE) {
  if ($col1) {
    $col1 = dba_statpack_short($col1, $bytes);
  }
  if ($col2) {
    $col2 = dba_statpack_short($col2, $bytes);
  }
  if ($col3) {
    $col3 = dba_statpack_short($col3, $bytes);
  }
  if (variable_get('dba_statpack_hide', TRUE) && !$col3) {
    return '';
  }
  else {
    return dba_statpack_columns(array($title, $col1, $col2, $col3));
  }
}

function dba_mysql_statpack_statement($title, $first, $last, $statements) {
  $delta = dba_statpack_short($last - $first);
  if ($delta > 0) {
    $col1 = "$delta (". dba_statpack_short(dba_statpack_to_percentage($delta / $statements[2])) .'%)';
  }
  else {
    $col1 = $delta;
  }
  $col2 = dba_statpack_short($delta / variable_get('dba_statpack_interval', DBA_STATPACK_INTERVAL));
  if ($last > 0) {
    $col3 = dba_statpack_short($last) .' ('. dba_statpack_short(dba_statpack_to_percentage($last / $statements[1])) . '%)';
  }
  else {
    $col3 = dba_statpack_short($last);
  }
  if (variable_get('dba_statpack_hide', TRUE) && !$col3) {
    return '';
  }
  else {
    return dba_statpack_columns(array($title, $col1, $col2, $col3));
  }
}

