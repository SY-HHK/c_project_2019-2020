<?php
$serveur = 'localhost';
$login = 'site';
$mot_de_passe = 'bdd123';
$base_de_donnees = 'c_project';
$charset = 'UTF8';
$port = 3308;

$pdo = new PDO('mysql:host='.$serveur.';dbname='.$base_de_donnees.';charset='.$charset, $login, $mot_de_passe);
?>
