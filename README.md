Projet MNT : Modèle Numérique de terrain



Ce projet présente une solution pour la génération d’une image 2D repéesentant, par niveaux de couleurs, les différentes altitudes d’un terrain 2.5D.


1 Execution

	Requis: 
		- Cmake au minimum la version 2.6
		- Avoir installer la librairie de projection Proj 7.2.1


	Afin de simplifier l'execusion, toutes les commandes permettants de 		générer l'executable se trouvent dans le fichier shell build.sh. On s	e place dans le repertoire create_raster et on l'execute comme suit: 
		- sh build.sh 
		ou 

		- ./build.sh


	Un executable create_raster est géneré et on le compile en ajoutant 		deux paramètres : 
		- le premier qui est le chemin vers le fichier de données. 			Lorsqu'on 	se place dans le dossier build,      			c'est ../src/Guerledan.txt

		- le second est la largeur de l'image, 800 par exemple. 


	En fin, on obtient deux images binaires dans le dossier build:
	- Rendu_Guerledan.PGM, une image en nuance de gris 
	- Rendu_Guerledan.PPM, une image en couleur 


2 Documentation
	Le documentation du code se trouve dans le fichier html              		doc/html/annotated.html


Remarque: 
	Lorsqu'on lance le programme on a un terminal vide pendant une 		minute, pas de panique les prints on été retié pour que le programme 	tourne plus vite. Le programme tourne !
