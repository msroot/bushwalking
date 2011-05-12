<?php

function bw_testmodule_form(){
	global $user;
	watchdog('testmodule', 'loading test page');
	$form['username_display'] = array(
		'#type' => 'item',
		'#title' => 'Username',
		'#value' => $user->name,
	);

	$form['user_clear_status'] = array(
		'#type' => 'checkbox',
		'#title' => 'reset rambo status',
		'#default_value' => 1,
	);
	
	$form['save_btn'] = array(
		'#type' => 'submit',
		'#value' => 'Save',
		
	);
	return $form;
}

function bw_testmodule_form_validate($form, &$form_state){
	$reset = $form_state['values']['user_clear_status'];
	if($reset){
		form_set_error('Reset rambo status', 'Sorry can not reset this user');
	}
}

function bw_testmodule_form_submit($form, &$form_state){
	$reset = $form_state['values']['user_clear_status'];
	drupal_set_message('User data has been saved');
	drupal_goto('/node/1');
}
?>