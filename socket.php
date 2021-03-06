<?php
include("config.php");

//test des erreurs possibles
if (($socket = socket_create_listen ( 1234 )) == FALSE) {
	echo "socket_create_listen() a échoué : " . socket_strerror ( socket_last_error ($socket) ) . "\n";
	exit ( 1 );
}
// Modification de l'option SO_REUSEADDR à la valeur 1 !
if (!socket_set_option($socket, SOL_SOCKET, SO_REUSEADDR, 1)) {
	echo 'Impossible de définir l\'option du socket : '. socket_strerror(socket_last_error($socket)) . "\n";
	exit ( 1 );
}
//bind sur une adresse particulière
/*
if(socket_bind ( $socket, "127.0.0.1", 1234 )==FALSE){
	echo "socket_bind() a échoué : " . socket_strerror ( socket_last_error ($socket) ) . "\n";
	exit ( 1 );
}
*/
if(socket_listen ( $socket )==FALSE){
	echo "socket_listen() a échoué : " . socket_strerror ( socket_last_error ($socket) ) . "\n";
	exit ( 1 );
}

//si aucune erreur -->
socket_set_nonblock ( $socket );
$clients = array ();
while ( TRUE ) {
	if ($c = socket_accept ( $socket )) {
		echo "nouvelle connexion \n";
		// Passage en mode non bloquant de la socket du client
		socket_set_nonblock ( $c );
		// Ajout de la socket cliente au tableau
		$clients [] = $c;
	}
	// On répond au clients qui ont envoyés un message
	for($i = 0; $i < sizeof ( $clients ); $i ++) {
		$c = $clients [$i];
		if ($buf = socket_read ( $c, 2048 )) {
			if(strstr($buf,"login:")) {
				echo "Connection...\n";
				$email_user = explode("&&&",explode("login:",$buf)[1]);
				$password = $email_user[1];
				$email_user = $email_user[0];
				$stmt = $pdo->prepare("SELECT * FROM USER WHERE email_user = ? && password = ?");
				$stmt->execute(array($email_user,$password));
				$login_accept = $stmt->rowCount();
				if ($login_accept == 1) {
					echo "Succesful ! \n";
					socket_write ( $c, "1" );
				}
				else {
					echo "Denied ! wrong mail or password; \n";
					socket_write ( $c, "0" );
				}

				////
			}
			if(strstr($buf,"email_user:")) {
		$new_email_user = explode("email_user:",$buf);
		$new_email_user = $new_email_user[0];
		$stmt = $pdo->prepare("UPDATE USER SET email_user = ? where id_user = 1");
		$stmt->execute(array($new_email_user));
		}
		if(strstr($buf,"password:")) {
		$new_password = explode("password:",$buf);
		$new_password = $new_password[0];
		$stmt = $pdo->prepare("UPDATE USER SET password = ? where id_user = 1");
		$stmt->execute(array($new_password));
		}
		}
	}
	// On efface les sockets fermées
	for($i = 0; $i < sizeof ( $clients ); $i ++) {
		$c = $clients [$i];
		if ($c == FALSE) {
			$clients = array_splice ( $clients, $i, 1 );
		}
	}
  usleep(500);//pause de 1 demi sec
}
socket_close ( $socket );




?>
