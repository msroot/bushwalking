<?php
require_once "model.php";

// Status can be: available, broken, booked
class equipment extends model{
	function __construct(){
		parent::__construct('equipment');
		$this->pageSize == 100000;
	}}  
	
	
 