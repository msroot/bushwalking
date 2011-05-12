<?php
mysql_connect("localhost", "root", "root") or
die("Could not connect: " . mysql_error());
mysql_select_db("drupal");

$debug = true;



/*---------------------------------------*/
getByUserId("1");
getAll();
/*---------------------------------------*/



function getByUserId($id){
	$q = "SELECT * FROM hire WHERE user_id ={$id};";
	$result = mysql_query($q) or die(mysql_error());
	$stack= getDBTables($result);

	if ($debug=true){ echo "<pre>"; print_r($stack);}
	return $stack;
}


function getAll(){
	$q = "SELECT * FROM hire ;";
	$result = mysql_query($q) or die(mysql_error());
	$stack= getDBTables($result);

	if ($debug=true){print_r($stack);}
	return $stack;
}


function update($hire = array()){


}

function delete($id){


}



function add($hire){

	$q  ="INSERT INTO hire (supplier_id, supplier_name, city)
VALUES (5005, 'NVIDIA', 'LA');";
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



?>