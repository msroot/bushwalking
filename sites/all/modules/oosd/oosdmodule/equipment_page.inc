<?php

// include  model classes
module_load_include('inc', 'oosdmodule', 'equipment');

/******************* controller functions *******************/

/******************* get methods *******************/

function bw_get_update(){ 
	// FIXME get from db
	$equipment = array("id" => 1, "category" => "tent", "name" => "Tent 3 man", "description" => "good for 3 man", "price" => 10 );
	return bw_equipment_form($equipment, "update", "");
}

function bw_get_add(){ 
	// TODO do this automaticaly
	$equipment = array("id" => "", "category" => "", "name" => "", "description" => "", "price" => "" );
	return bw_equipment_form($equipment, "add", "");
}

/******************* post methods *******************/


function bw_post_add(){
	// FIXME do on DB
	drupal_set_message('Equipment added');
	drupal_goto('equipment');
}

function bw_post_update(){
	// FIXME do on DB	
	drupal_set_message('Equipment updated');
	drupal_goto('equipment');
}

function bw_get_delete(){
	// FIXME do on DB	
	drupal_set_message('Equipment deleted');
	drupal_goto('equipment');
}

/******************* view functions *******************/

// Generate the list of equipment
function bw_list_equipment($equipmentList){
	global $user;

	$form .= '<table border="0" cellspacing="5" cellpadding="5">';
	$form .= "<tr>";

	foreach($equipmentList[0] as $key => $val){
		$form .= "<th>$key</th>";
	}
	
	$form .= "</tr>";

	foreach($equipmentList as $equipment){
		$form .= "<tr>";
		foreach($equipment as $key => $val){
			$form .= "<th>$val</th>";
		}
		$form .= '<th><a href="equipment/?action=update&id='.$equipment["id"].'">update</a></th>';
		$form .= '<th><a href="equipment/?action=delete&id='.$equipment["id"].'">delete</a></th>';
		$form .= '</tr>';
	}       
	$form .= '</table>';
	$form .= '<p><a href="equipment/?action=add">add equipment</a></p>';
	return $form;
}

function bw_equipment_form($equipment, $action_name, $action_path){
	// $form = '<form action="'.$action_path.'" method="post" accept-charset="utf-8">';
	$form = '<form action="'.$action_path.'" method="post" accept-charset="utf-8">';
	$form .= '<input type="hidden" name="'.$action_name.'" value="'.$action_name.'">';

	foreach($equipment as $key => $val){
		$form .= '<label for="'.$key.'">'.$key.':</label><input type="text" name="'.$key.'" value="'.$val.'" id="'.$key.'"><br />';
	}	

	$form .= '<input type="submit" name="'.$action_name.'_btn" value="'.$action_name.'" id="'.$equipmen['id'].'">';
	$form .= '</form>';
	return $form;
}
?>