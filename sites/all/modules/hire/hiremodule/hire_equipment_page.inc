<?php

function bw_hire_equipment_form(){
	global $user;
	
    // echo "HELLO";
    // watchdog('hiremodule', 'loading test page');
    // $form['username_display'] = array(
    //  '#type' => 'item',
    //  '#title' => 'Username',
    //  '#value' => $user->name,
    // );
    // 
    // $form['user_clear_status'] = array(
    //  '#type' => 'checkbox',
    //  '#title' => 'reset rambo status',
    //  '#default_value' => 1,
    // );
    // 
    // $form['save_btn'] = array(
    //  '#type' => 'submit',
    //  '#value' => 'Save',
    //  
    // );
    // return $form;
    return "<p>HELLO</p> $user->name";
}

function bw_hello(){
	global $user;
    return "<p>HELLO $user->name</p> ";
}


// Generate the list of equipment
function bw_list_equipment($equipmentList){
	global $user;
	$table = '<table border="0" cellspacing="5" cellpadding="5">';
	$table .= "<tr>";
	
	foreach($equipmentList[0] as $key => $val){
	    $table .= "<th>$key</th>";
	}
	$table .= "</tr>";
	
	foreach($equipmentList as $equipment){
	    $table .= "<tr>";
	    foreach($equipment as $key => $val){
	        $table .= "<th>$val</th>";
	    }
	    $table .= "</tr>";
	}	
	$table .= '</table>';
	return $table;
}


function bw_hire_equipment_form_validate($form, &$form_state){
	$reset = $form_state['values']['user_clear_status'];
	if($reset){
		form_set_error('Reset rambo status', 'Sorry can not reset this user');
	}
}

function bw_hire_equipment_form_submit($form, &$form_state){
	$reset = $form_state['values']['user_clear_status'];
	drupal_set_message('User data has been saved');
	drupal_goto('/node/1');
}
?>