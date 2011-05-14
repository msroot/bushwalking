<?php

?>
<div class="profile">
<h1 class="thankyou"  >Informations for <?php echo $user->name; ?> / <?php echo $user->mail; ?></h1>
<br />
<hr/>

  <?php 
  
 
  
  //print $user_profile;   
  
 $expires = db_result(db_query('SELECT expires FROM {membership} where uid=%d', $user->uid));
 $expires_day = format_date($expires, 'custom', t('Y-m-d'));
 
 $member_start = db_result(db_query('SELECT lastmod FROM {membership} where uid=%d', $user->uid));
 $expires_start = format_date($member_start, 'custom', t('Y-m-d'));
 
 global $user;
 $userRegister = format_date($user->created, 'custom', t('Y-m-d'));

  
 
  $role = db_result(db_query('SELECT r.name FROM {users_roles} ur LEFT JOIN {role} r ON r.rid=ur.rid WHERE ur.uid=%d LIMIT 1', $user->uid));
  if ($role == "member"){ 

?><div>
<h1 class="membeship-i"  >Membership Status:</h1>

<h3 class="membeship-info">User register: <?php print_r ($userRegister) ;?> </h3>
<h3 class="membeship-info">Membership Start: <?php print_r ($expires_start) ;?> </h3>
<h3 class="membeship-info">Membership Expires: <?php print_r ($expires_day) ;?> </h3>
<p>Renew now your Membership with paypall:</p>

<input type="submit" name="book_btn" value="PAY NOW SECURE WITH PAYPALL">
<a href=""><img  style="float:right; padding-bottom:10px;" src="http://www.allprivatelabelcontent.com/paypall.gif"></a>
 
<br /><br />
<br />
<br />

<h1 class="membeship-i"  >Hired Equipments under your name:(<?php echo $user->name; ?> / <?php echo $user->mail; ?>)</h1>

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
                  

<h1 class="thankyou"  >Thank you for using Bushwalking Club</h1>

</div>
<?php } ?> 


<?php // print_r($user);?>

</div>
