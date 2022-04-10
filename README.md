# Projet M1 IAFA - Informatique Graphique

## Utilisation

Pour utiliser l'application, le l'executable est disponible dans /application/BezierCurveProject.exe. Pour la modifier il est conseillé d'utiliser Visual Studio avec glm et Qt (version 5 au moins) d'installés. Il suffit de charger la solution fournie avec Visual Studio: https://github.com/Julian-Villeneuve/BezierCurve/blob/main/BezierCurveProject.sln

## Commandes
- Simulation courbe de Bézier:

espace -> ouvre la simulation de surface de Bézier

clic_gauche -> ajoute des points (plus fonctionnel, à corriger : calcule la nouvelle courbe à chaque ajout de point)

- Simulation surface de Bézier:

espace -> ouvre la simulation de courbe de Bézier

clic enfoncé -> déplacer la caméra

molette_souris -> zoom/dezoom


## Bézier Curve

### Mesh
La classe Mesh est la classe la plus utilisée du projet, servant à construire et dessiner tout ce qui va apparaître à l'écran en utilisant une structure de Vertex
très basique ne prenant qu'une position (plus tard prenant aussi une normale pour calculer la lumière). La seule exception n'utilisant pas de mesh est la classe Point.

### Curve
C'est là que l'on va calculer les points de la courbe de Bézier avec la méthode récursive expliquée au début de la rubrique suivante. Grâce à ces points obtenus, on pourra calculer les points de la surface de Bézier.

### Ajout de points de contrôle

Pour l'instant il faut ajouter les points de contrôle à la main, la méthode d'ajout en temps réel avec la souris n'est pas fonctionnelle (ce sera avec un clique gauche, cela n'ajoute que des points tous seuls pour le moment).

La méthode utilisée est la méthode récursive, avec la formule de Wikipédia (https://en.wikipedia.org/wiki/B%C3%A9zier_curve) suivante:
![bezierRecursiveFormula](https://user-images.githubusercontent.com/59332180/162328081-d602c7e6-1e71-40d5-af09-f05f35da0771.png)

On initialise les points en vec3 :
``` cpp
glm::vec3 point1 = glm::vec3(0.5, -0.5, 0.0);
glm::vec3 point2 = glm::vec3(0.5, 0.5, 0.0);
glm::vec3 point3 = glm::vec3(-0.5, 0.5, 0.0);
```

Dans la méthode initializeGL() de la classe OpenGLWidget, on doit ajouter les points dans 2 listes différentes:
- La liste de points de la classe Point, affichant simplement les points:
```	cpp
_points = new Points();
_points->Add(point1);
_points->Add(point2);
_points->Add(point3);
```

- Ces mêmes points, dans un vecteur de Vertex qui serviront ici à calculer la courbe de Bézier, et dessiner ce dernier ainsi que le polygone de contrôle
``` cpp
struct Vertex v1, v2, v3;
v1.pos = point1;
v2.pos = point2;
v3.pos = point3;
controlVertices.push_back(v1);
controlVertices.push_back(v2);
controlVertices.push_back(v3);
```

### Résultats obtenus après ajout de points

Avec ces 3 points pris en exemple, on obtient l'image suivante après l'appel des méthodes Draw correspondantes:
``` cpp
_points->Draw();
_curve->_curveMesh->Draw(_shaderCurve);
_controlPolygon->DrawPolygon(_shaderPoly);
```
![Bezier3points](https://user-images.githubusercontent.com/59332180/162328015-77f40d2a-3bbe-42d8-b96f-72d963a2bf02.png)

Il suffit donc de rajouter quelques lignes selon le modèle précédent afin de compléter le vecteur des points de contrôle et la liste de points pour ajouter un point à l'écran et étendre la courbe, ou simplement modifier les coordonnées des points individuellemnt.
Par exemple si on ajoute ces deux points l'un après l'autre de la même manière que les autres points:
``` cpp
glm::vec3 point4 = glm::vec3(-0.5, -0.5, 0.0);
glm::vec3 point5 = glm::vec3(0.0, 0.0, 0.0);
```
On obtient successivement:

![Bezier4points](https://user-images.githubusercontent.com/59332180/162328023-7855ef0e-59e4-4e60-8670-3e4c54f712e2.png)

Puis:

![Bezier5points](https://user-images.githubusercontent.com/59332180/162328056-aaa07141-e4e6-4ebb-b020-67d74ce1f60f.png)


## Bézier Surface Patch

Appuyez sur espace pour passer à la simulation de surface de Bézier.

### Caméra

Le clic souris enfoncé permet de déplacer la caméra autour de l'objet, et la molette à zoomer ou dézoomer.

### Surface
Actuellement, les points de contrôle ont un axe Z générés aléatoirement, ce qui donnera une surface aléatoire à chaque lancement de la simulation ou en appuyant deux fois sur espace (la touche faisant cela à volonté sans recharger la simulation n'est pas fonctionnelle)

Sinon on peut ajouter ou modifier les points de contrôle de la même manière qu'avant. C'est dans la méthode initializeGL() de la classe OpenGLPatch,
on ajoute des points de coordonnées glm::vec3, créer un Vertex prenant ces coordonnées puis le push dans le vecteur _controlPoints de points de contrôle.
Une fois envoyés dans la classe Curve, tous les points nécessaires pour dessiner une surface seront calculés, puis après les appels de draw, on obtient
une surface aléatoire et sans maillage suivante:

https://user-images.githubusercontent.com/59332180/162547382-ddcfa92c-518b-4567-84c7-cb979174414e.mp4

Puis avec un plus grand nombre de points dans les courbes, modifiable via la variable step dans la méthode getFullSurface() de la classe surface.cpp
(ici avec 100 points):





https://user-images.githubusercontent.com/59332180/162626311-f31bb6b5-3a58-4903-a894-01a5732cb062.mp4

### Maillage
Comme le montrent les vidéos précédentes, c'est plutôt dur de s'y retrouver sans maillage avec un nombre peu élevé de points, et ça fait un peu mal aux yeux
avec beaucoup de points (même si c'est très joli). 
On va donc faire un maillage en plaçant les indices des vertices correspondants aux points dans l'ordre dans lequel on veut dessiner les mailles.


## Evaluation des résulats obtenus et rétrospective sur le projet

Pour ce qui est des résulats je suis globalement satisfait. Ce projet m'a surtout permis d'apprendre les bases de l'informatique graphique et d'OpenGL.
Que ce soit la simulation de courbe ou de surface, je trouve les résultats au niveau de mes attentes et plutôt agréable à contempler.

Cependant, il y a beaucoup de fonctionnalités que je n'ai pas réussi ou pas eu le temps de faire. Pour ce que je n'ai pas réussi à faire:

- Cliquer pour ajouter un point et calculer la nouvelle courbe. Le problème vient selon moi de ma fonction setupMesh() visant à envoyer les nouvelles données
au GPU afin de pouvoir draw la nouvelle courbe obtenue, mais cette fonction fait simplement crash l'application.

- Maillage de la surface de Bézier. Ici, c'est la fonctionnalité la plus importante selon moi que je voulais faire mais qui ne marche pas. Certes les surfaces
qu'on obtient sont jolies et plutôt originales, mais il faut un maillage avec des triangles bien faite pour pouvoir calculer les normales, ajouter de la lumière,
ou encore de la texture.

- Randomization de la surface sans avoir à charger une nouvelle simulation. Encore une fois, c'est la méthode setupMesh() qui fait défaut ici. Cette
fonctionnalité aurait été très facile à coder (en soit c'est déjà fait puisque la surface est générée aléatoirement), mais sans cette méthode je n'ai pas 
trouvé de solution.

- Parallélisation du code. Je voulais faire ça au moins après avoir obtenu un maillage et une lumière satisfaisante puis que je trouve ça plus important. Mais actuellement la surface met 2 secondes à se charger pour 100x100 points, et quasiment une minute (voire fait crash l'application) lorsque l'on veut 1000 par 1000 points. Avec des compute shaders et les calculs faits sur le GPU, cela peut être fait presque instantanément, rien n'est optimisé dans la version actuelle du code.















