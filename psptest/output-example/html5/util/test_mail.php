#!/usr/local/bin/php
<?php
    $notes = 
    "\n" .
    "--------------------\n" .
    "\n" .
    "usage: $argv[0] email-address\n" .
    "prints current mail config\n" .
    "sends test message\n" .
    "\n";

require_once "/opt/lampp/htdocs/psptest/ajax/mail.php";

PEAR::setErrorHandling(PEAR_ERROR_PRINT, "PEAR::Mail error: %s\n");

$json = json_decode( file_get_contents( "__appconfig__" ) );

echo "from __appconfig__:\n";
print_r( $json->mail );

if ( !isset( $argv[ 1 ] ) ) {
    echo $notes;
    exit;
}

if ( isset( $json->mail->smtp ) ) {
    $smtp = "smtp";
} else {
    $smtp = "sendmail";
}

echo "test message to $argv[1] using $smtp\n";

$host = gethostname();

if ( mymail( $argv[ 1 ], "[$host][psptest][test message][$smtp]", "This is a psptest test message from host named $host send by $argv[0] using $smtp" ) )
{
    echo "error found in sending\n";
} else {
    echo "send looks ok, now check the mail for $argv[1] to make sure it went throgh\n";
}

exit;
?>

    
