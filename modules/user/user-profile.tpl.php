<?php

?>
<div class="profile">

  <?php 
  
 
  
  print $user_profile;   
  
 $expires = db_result(db_query('SELECT expires FROM {membership} where uid=%d', $user->uid));
 $expires_day = format_date($expires, 'custom', t('Y-m-d'));
 
 
  $role = db_result(db_query('SELECT r.name FROM {users_roles} ur LEFT JOIN {role} r ON r.rid=ur.rid WHERE ur.uid=%d LIMIT 1', $user->uid));
  if ($role == "member"){ 

?><div>
<h1>Membership Status:</h1>
<hr />
<h3>Membership expires: <?php print_r ($expires_day) ;?> </h3>
<p>Renew now your Membership with paypall:</p>
<a href=""><img src="http://www.allprivatelabelcontent.com/paypall.gif"></a>
<hr />


<br />
<br />

<h1>Hired Equipments:</h1>

<table border="0" cellpadding="6" cellspacing="5"><tbody>
<tr>
<th>id</th>
<th>equipment</th>
<th>date start</th>
<th>date end</th>
<th>returned</th>
<th>status</th>
<th>pay now</th>

 <?php 
$uid=$user->uid;
$q=('SELECT * FROM `hire` WHERE user_id='.$uid.'');

 $hired = pager_query($q, 900, 0, NULL);

while($total = db_fetch_object($hired)) {

  $name = db_result(db_query('SELECT name FROM equipment WHERE id =%d LIMIT 1', $total->equipment_id));

echo '<tr><th>'. $total->equipment_id.' </th>';
echo '<th>'. $name.' </th>';
echo '<th>'.$total->date_start.'</th>';
echo '<th>'.$total->date_end.'</th>';
echo '<th>'.$total->returned.'</th>';
echo '<th>'.$total->status.'</th>';
echo '<th><a href="">pay now</a></th></tr>';
}
?>
</th></tr></tbody></table>
                  

</div>
<?php } ?> 


</div>
