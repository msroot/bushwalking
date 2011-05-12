<?php

function bw_hire_equipment_form(){
    global $user;

    watchdog('hiremodule', 'loading hire page');

    $form['equipment_list'] = array(
        '#type' => 'item',
    '#title' => 'Equipment list',
    '#value' => bw_list_equipment(BWEquipment::getAll()),
    );

    $form['save_btn'] = array(
        '#type' => 'submit',
    '#value' => 'Save',
    );

    return $form;
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
    drupal_goto('equipment');
}

function bw_hello(){
    global $user;
    return "<p>HELLO $user->name</p> ";
}

// Generate the list of equipment
function bw_list_equipment($equipmentList){
    global $user;

    $form = '<form action="equipment" method="get" accept-charset="utf-8">';
	$form .= '<input type="hidden" name="action" value="book">';
    $form .= '<table border="0" cellspacing="5" cellpadding="5">';
    $form .= "<tr>";

    foreach($equipmentList[0] as $key => $val){
        $form .= "<th>$key</th>";
    }
	$form .= "<th>Select</th>";
    $form .= "</tr>";

    foreach($equipmentList as $equipment){
        $form .= "<tr>";
        foreach($equipment as $key => $val){
            $form .= "<th>$val</th>";
        }
        $form .= '<th><input type="radio" name="id" value="'.$equipment["id"].'" /></th>';
		$form .= '<th><a href="equipment/?action=update&id='.$equipment["id"].'">update</a></th>';
		$form .= '<th><a href="equipment/?action=delete&id='.$equipment["id"].'">delete</a></th>';
        $form .= '</tr>';
    }       
    $form .= '</table>';
	$form .= '<label for="date_from">Date From:</label><input type="text" name="date_from" value="" id="date_from">';
	$form .= '<label for="date_to">Date to:</label><input type="text" name="date_to" value="" id="date_to">';
    $form .= '<input type="submit" name="book_btn" value="book" id="book_btn">';
    $form .= '</form>';
    return $form;
}

function bw_equipment_form($equipment, $action_name, $action_path){
	$form = '<form action="'.$action_path.'" method="get" accept-charset="utf-8">';
	$form .= '<input type="hidden" name="action" value="book">';
		
    foreach($equipment as $key => $val){
        $form .= '<label for="'.$key.'">'.$key.':</label><input type="text" name="'.$key.'" value="'.$val.'" id="'.$key.'">';
    }
    $form .= '<input type="submit" name="'.$action_name.'_btn" value="'.$action_name.'" id="'.$equipmen['id'].'">';
    $form .= '</form>';
    return $form;
}
?>