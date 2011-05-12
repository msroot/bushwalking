<?php

// include  model classes
module_load_include('php', 'oosdmodule', 'equipment');

/******************* controller functions *******************/

/******************* get methods *******************/
function bw_index(){
	$equipment = new equipment();
	return bw_list_available_equipment($equipment->getAll());
}

/******************* post methods *******************/

function bw_post_book(){
    global $user;
	
	// TODO $user->uid;
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
	$form .= '<label for="date_from">Date From:</label><input type="text" name="date_from" value="" id="date_from">';
	$form .= '<label for="date_to">Date to:</label><input type="text" name="date_to" value="" id="date_to">';
    $form .= '<input type="submit" name="book_btn" value="book" id="book_btn">';
    $form .= '</form>';
    return $form;
}
?>