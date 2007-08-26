<?

// hostname or ip of server (for local testing, localhost should work)
$dbServer='localhost';

// username and password to log onto db server (what you entered in Step 4)
$dbUser='rude';
$dbPass='bullshit';

// name of database (what you created in step 4)
$dbName='love';

$link = mysql_connect("$dbServer", "$dbUser", "$dbPass") or die("Could not connect");
mysql_select_db("$dbName") or die("Could not select database");

?>