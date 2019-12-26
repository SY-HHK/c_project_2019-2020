<?php
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
		print_r("nouvelle connexion");
		// Passage en mode non bloquant de la socket du client
		socket_set_nonblock ( $c );
		// Ajout de la socket cliente au tableau
		$clients [] = $c;
	}
	// On répond au clients qui ont envoyés un message
	for($i = 0; $i < sizeof ( $clients ); $i ++) {
		$c = $clients [$i];
		if ($buf = socket_read ( $c, 2048 )) {
			echo $buf;
			socket_write ( $c, "You said : " . $buf );
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
