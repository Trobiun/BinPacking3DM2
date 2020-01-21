Le programme se lance automatiquement en mode 3D.
Pour le mode 3D :

Le programmes va rechercher les conteneurs qu'il peut utiliser dans un fichier CSV nommé 3DConteneur qui doit être placé dans le dossier de l'éxécutable.
Ce fichier doit être structuré de la manière suivante : CoteX;CoteY;CoteZ;nombreDispo
CoteY représente la hauteur et CoteX et CoteZ les deux autres longueurs du cubes (supposé interchangeable car l'objet peut être orienté).
nombreDispo est le nombre de fois que l'on peut utiliser ce conteneur, -1 si infinité.

Le programmes va rechercher les composant à placer dans un fichier CSV nommé 3DComposant qui doit être placé dans le dossier de l'éxécutable.
Ce fichier doit être structuré de la manière suivante : Id;CoteX;CoteY;CoteZ
CoteY représente la hauteur et CoteX et CoteZ les deux autres longueurs du cubes (supposé interchangeable car l'objet peut être orienté).

En mode 3D certaines touche ont été assigné pour facilité l'utilisation : 
touche Entrée : place la vue sur le premier conteneur ( conteneur d'id 0).
touche 5 du pavé numérique : place la vue sur le conteneur actuel.
touche 6 du pavé numérique : remet la vue sur le conteneur suivant.
touche 4 du pavé numérique : remet la vue sur le conteneur précédent.
espace : permet le passage du mode fil de fer au mode opaque et inversement.
les flèches : fais tourner la camera autour du cube.

Le mode 2D est toujours disponible dans le code du projet, cependant pour l'activé il faut aller modifier une variable manuellement dans le code.
La partie 2D du projet a été abandonné au passage a la 3D et n'est donc plus maintenu, ce qui explique la précense de nombreux bug qui ne sont plus présent dans la version 3D.
Il n'est présent que pour avoir une vue sur le code de début du projet.

