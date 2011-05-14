<?php
require_once "model.php";


// HIRE status can be: booked, started, finished
class hire extends model{
	function __construct(){
		parent::__construct('hire');
		$this->pageSize == 100000;
	}}  
	
	// function getStatuses(){
	// 	return array("booked, started, finished");
	// }