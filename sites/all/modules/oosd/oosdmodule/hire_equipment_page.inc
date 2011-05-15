<?php
/***********************************************************************************
#  University: RMIT University - Melbourne, Australia
# School: Computer Science and Information Technology
# Subject:  ISYS1083 Object Oriented Software Design
# Assignment : Final OOSD Group Assignment
# Project Title: Bushwalking Web Site
#  Semester:  1 - 2011
---------------------------------------------------------------------------------
Hire equipment Module

Module is responsible to handle all admin and users functionality
Users/Members  can hire and  equipment  with the given dates if equipment  is available
Administrators can manage equipments (Create, Read, Upade, Delete)
Administrators can manage hires (user hire an equipment) Create, Read, Upade, Delete

Group Members:
* Amruta Varshini - TL (s3272373)
* Emil B. Kjer (s3298554)
* Victor Nava (s3252905)
* John Kolovos (s3289732)
* Stefan Fuch (s3260968)
---------------------------------------------------------------------------------
@author Victor Nava
@author John Kolovos
***********************************************************************************/

// include  model classes
module_load_include('php', 'oosdmodule', 'equipment');
module_load_include('php', 'oosdmodule', 'hire');

/******************* controller functions *******************/

/******************* get methods *******************/
function bw_index(){
	$equipment = new equipment();
	return bw_list_available_equipment($equipment->getAllBy("status", "available"));
}

/******************* post methods *******************/

function bw_post_book(){
    global $user;
	$hire = new hire();
	$equipment = new equipment();
		
	// check if equipment exist
	$equipmentObj = $equipment->get($_POST["id"]);
	if(!$equipmentObj){
		drupal_set_message('There was a problem hiring this equipment, please try again.');
	    drupal_goto('hire_equipment');
	}
	
	$hireObj = array(
		"equipment_id" => $_POST["id"],
		"user_id" => $user->uid,
		"date_start" => $_POST["date_start"],
		"date_end" => $_POST["date_end"],
		"returned" => "",
		"status" => "booked"
	);
	
	$hire->create($hireObj);
	$equipmentObj["status"] = "booked";
	$equipment->update($equipmentObj);
	
	drupal_set_message('Equipment has been booked.');
    drupal_goto('hire_equipment');
}

/******************* view functions *******************/

// Generate the list of equipment
function bw_list_available_equipment($equipmentList){
    global $user;

    $form = '<form action="hire_equipment" method="post" accept-charset="utf-8">';
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
        $form .= '</tr>';
    }       
    $form .= '</table>';
	$form .= '<ul><li><label for="date_start">Date Start:</label><input type="text" class="date-pick" name="date_start" value="" id="date_start"></li>';
	$form .= '<li><label for="date_end">Date End:</label><input type="text" class="date-pick" name="date_end" value="" id="date_end"></li></ul>';
    $form .= '<input type="submit" name="book_btn" value="BOOK NOW" id="book_btn">';
    $form .= '</form>';
    return $form;
}
?>