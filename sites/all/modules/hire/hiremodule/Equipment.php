<?php
mysql_connect("localhost", "root", "root") or
die("Could not connect: " . mysql_error());
mysql_select_db("drupal");

$debug = true;

/*---------------------------------------*/
getById ("1");
getAll();
/*---------------------------------------*/


function getById($id){
	$q = "SELECT * FROM equipment WHERE id ={$id};";

	$result = mysql_query($q) or die(mysql_error());
	$stack= getDBTables($result);

	if ($debug=true){ echo "<pre>"; print_r($stack);}
	return $stack;

}


function getAll(){
	//$q = "SELECT * FROM equipment where status=1;";
	$q = "SELECT * FROM equipment ;";

	$result = mysql_query($q) or die(mysql_error());
	$stack= getDBTables($result);

	if ($debug=true){ echo "<pre>"; print_r($stack);}
	return $stack;

}


function getAllByCategory($cat){
	$q = "SELECT * FROM drupal.equipment group by category ;";

	$result = mysql_query($q) or die(mysql_error());
	$stack= getDBTables($result);

	if ($debug=true){ echo "<pre>"; print_r($stack);}
	return $stack;

}


function update($eq){

	$q = "";
}

function delete($id){

	$q = "";
}



function add($eq ){
	$q = "";
}






function getDBTables($result)
{
	$table_result=array();
	$r=0;
	while($row = mysql_fetch_assoc($result)){
		$arr_row=array();
		$c=0;
		while ($c < mysql_num_fields($result)) {
			$col = mysql_fetch_field($result, $c);
			$arr_row[$col -> name] = $row[$col -> name];
			$c++;
		}
		$table_result[$r] = $arr_row;
		$r++;
	}
	return $table_result;
}