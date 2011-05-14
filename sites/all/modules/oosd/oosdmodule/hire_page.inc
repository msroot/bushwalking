<?php

// include  model classes
module_load_include('php', 'oosdmodule', 'hire');
module_load_include('php', 'oosdmodule', 'equipment');

/******************* controller functions *******************/

/******************* get methods *******************/

function bw_index(){
	$hire = new hire();
	return bw_list_all($hire->getAll());
}

function bw_get_add(){ 
	$hire = new hire();
	$fields = array();
	foreach($hire->getTableColumns($hire->tableName) as $col){
		$fields[$col] = "";
	}
	return bw_form($fields, "add", "", $hire->getStatuses());
}
 
function bw_get_update(){ 
	$hire = new hire();
	$e = $hire->get($_GET[id]);
	return bw_form($e, "update", "", $hire->getStatuses());
}

function bw_get_delete(){
	$hire = new hire();
	// TODO handle errors
	$hire->delete($_GET['id']);
	drupal_set_message('Hire deleted');
	drupal_goto('hire');
}

/******************* post methods *******************/
 
function bw_post_add(){
	$hire = new hire();
	// TODO handle errors
	$hire->create($_POST);
	drupal_set_message('Hire added');
	drupal_goto('hire');
}

function bw_post_update(){
	$hire = new hire();
	// TODO handle errors
	// change the status of the equipment also
	if($_POST["status"] == "finished"){
		$equipment = new equipment();
		$equipmentObj = $equipment->get($_POST["equipment_id"]);
		$equipmentObj["status"] = "available";
		$equipment->update($equipmentObj);
	}
	$hire->update($_POST);
	drupal_set_message('Hire updated');
	drupal_goto('hire');
}


/******************* view functions *******************/

function bw_list_all($hireList){
	global $user;

	$h = '<p><a href="hire/?action=add">add hire</a></p>';
	$h .= '<table border="0" cellspacing="5" cellpadding="5">';
	$h .= "<tr>";

	foreach($hireList[0] as $key => $val){
		$h .= "<th>$key</th>";
	}
	
	$h .= "</tr>";

	foreach($hireList as $hire){
		$h .= "<tr>";
		foreach($hire as $key => $val){
			$h .= "<th>$val</th>";
		}
		$h .= '<th><a href="hire/?action=update&id='.$hire["id"].'">update</a></th>';
		$h .= '<th><a href="hire/?action=delete&id='.$hire["id"].'" onClick="return confirm(\'Are you sure?\')">delete</a></th>';
		$h .= '</tr>';
	}       
	$h .= '</table>';
	return $h;
}

// TODO refactor exactly the same as bw_equipment_form
function bw_form($hire, $action_name, $action_path, $statuses=array()){
	$form = '<form action="'.$action_path.'" method="post" accept-charset="utf-8">';
	$form .= '<input type="hidden" name="'.$action_name.'" value="'.$action_name.'">';
	$form .= '<input type="hidden" name="id" value="'.$hire['id'].'">';
	
	foreach($hire as $key => $val){
		if($key != 'id'){
			if($key == 'status'){
				$form .= '<label for="'.$key.'">'.$key.':</label><select name="'.$key.'" id="'.$key.'" size="1">';
				foreach($statuses as $status){
					if($equipment[status] == $status){
						$form .= '<option value="'.$status.'" selected="selected">'.$status.'</option>';
					}
					else{
						$form .= '<option value="'.$status.'">'.$status.'</option>';
					}
				}
				$form .= '</select>';
			} else {
				$class = preg_match("/date_/", $key) ? 'class="date-pick"' : "";
				$form .= '<label for="'.$key.'">'.$key.':</label><input type="text" '.$class.'name="'.$key.'" value="'.$val.'" id="'.$key.'">';
			}
			$form .= '<br />';
		}	
	}	

	$form .= '<input type="submit" name="'.$action_name.'_btn" value="'.$action_name.'" id="'.$hire['id'].'">';
	$form .= '</form>';
	return $form;
}
?>