<?php

// include  model classes
module_load_include('php', 'oosdmodule', 'equipment');

/******************* controller functions *******************/

/******************* get methods *******************/

function bw_index(){
	$equipment = new equipment();
	return bw_list_equipment($equipment->getAll());
}

function bw_get_update(){ 
	$equipment = new equipment();
	$e = $equipment->get($_GET[id]);
	return bw_equipment_form($e, "update", "");
}

function bw_get_add(){ 
	$equipment = new equipment();
	$fields = array();
	foreach($equipment->getTableColumns($equipment->tableName) as $col){
		$fields[$col] = "";
	}
	return bw_equipment_form($fields, "add", "");
}

/******************* post methods *******************/

function bw_post_add(){
	$equipment = new equipment();
	// TODO handle errors
	$equipment->create($_POST);
	drupal_set_message('Equipment added');
	drupal_goto('equipment');
}

function bw_post_update(){
	$equipment = new equipment();
	// TODO handle errors
	$equipment->update($_POST);
	drupal_set_message('Equipment updated');
	drupal_goto('equipment');
}

function bw_get_delete(){
	$equipment = new equipment();
		// TODO handle errors
	$equipment->delete($_GET['id']);
	drupal_set_message('Equipment deleted');
	drupal_goto('equipment');
}

/******************* view functions *******************/

// Generate the list of equipment
function bw_list_equipment($equipmentList){
	global $user;

	$h = '<p><a href="equipment/?action=add">add equipment</a></p>';
	$h .= '<table border="0" cellspacing="5" cellpadding="5">';
	$h .= "<tr>";

	foreach($equipmentList[0] as $key => $val){
		$h .= "<th>$key</th>";
	}
	
	$h .= "</tr>";

	foreach($equipmentList as $equipment){
		$h .= "<tr>";
		foreach($equipment as $key => $val){
			$h .= "<th>$val</th>";
		}
		$h .= '<th><a href="equipment/?action=update&id='.$equipment["id"].'">update</a></th>';
		$h .= '<th><a href="equipment/?action=delete&id='.$equipment["id"].'" onClick="return confirm(\'Are you sure?\')">delete</a></th>';
		$h .= '</tr>';
	}       
	$h .= '</table>';
	return $h;
}

function bw_equipment_form($equipment, $action_name, $action_path, $assoc=true){
	// $form = '<form action="'.$action_path.'" method="post" accept-charset="utf-8">';
	$form = '<form action="'.$action_path.'" method="post" accept-charset="utf-8">';
	$form .= '<input type="hidden" name="'.$action_name.'" value="'.$action_name.'">';
	$form .= '<input type="hidden" name="id" value="'.$equipment['id'].'">';
	
	foreach($equipment as $key => $val){
		if($key != 'id'){
			$form .= '<label for="'.$key.'">'.$key.':</label><input type="text" name="'.$key.'" value="'.$val.'" id="'.$key.'"><br />';
		}		
	}	

	$form .= '<input type="submit" name="'.$action_name.'_btn" value="'.$action_name.'" id="'.$equipment['id'].'">';
	$form .= '</form>';
	return $form;
}
?>