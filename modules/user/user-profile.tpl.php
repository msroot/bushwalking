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
<a href=""><img src="http://science-fiction-books.com.au/images/PayPall-logo.gif"></a>

</div>
<?php } ?> 


</div>
