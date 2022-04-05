# Projet M1 IAFA - Informatique Graphique

## Commandes
- Clavier:

c -> ouvre/réinitialise la simulation de courbe de Bézier

p -> ouvre/réinitialise la simulation de surface de Bézier

- Souris:

clic_gauche -> ajoute des points dans la simulation de courbe de Bézier

## Bézier Curve

### Mesh
La classe Mesh est la classe la plus utilisée du projet, servant à construire le maillage des courbes et surfaces de Bézier.

### Ajout de points de contrôle

Pour l'instant il faut ajouter les points de contrôle à la main, la méthode d'ajout en temps réel avec la souris n'est pas fonctionnelle (ce sera avec un clique gauche, cela n'ajoute que des points tous seuls pour le moment).

La méthode utilisée est la méthode récursive, avec la formule de Wikipédia (https://en.wikipedia.org/wiki/B%C3%A9zier_curve) suivante:
![Bezier Curve Recursive Formula](https://github.com/Julian-Villeneuve/BezierCurve/blob/main/res/bezierRecursiveFormula.png)

On initialise les points en vec3 :
``` cpp
glm::vec3 point1 = glm::vec3(0.5, -0.5, 0.0);
glm::vec3 point2 = glm::vec3(0.5, 0.5, 0.0);
glm::vec3 point3 = glm::vec3(-0.5, 0.5, 0.0);
```

Dans la méthode initializeGL() de la classe OpenGLWidget, on doit ajouter les points dans 3 listes différentes:
- La liste de points de la classe Point, affichant simplement les points:
```	cpp
_points = new Points();
_points->Add(point1);
_points->Add(point2);
_points->Add(point3);
```
- La liste de ces mêmes points dans un vecteur qui les enverra dans la classe Curve, qui calculera la courbe de Bézier résultante et la dessinera:
``` cpp
_pointsListCurve.push_back(point1);
_pointsListCurve.push_back(point2);
_pointsListCurve.push_back(point3);
```
- Toujours ces mêmes points, dans un vecteur de Vertex qui en soit fait doublon mais que j'ai séparé pour bien distinguer le polygone de la courbe:
``` cpp
struct Vertex v1, v2, v3, v4, v5;
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
_curve->_curveMesh->Draw();
_controlPolygon->DrawControl();
```
![Bezier Curve 3 points](https://github.com/Julian-Villeneuve/BezierCurve/blob/main/res/Bezier3points.png)

Il suffit donc de rajouter 3 lignes dans les 3 vecteurs ci-dessus pour ajouter un point et étendre la courbe, ou simplement modifier les coordonnées des points individuellemnt.
Par exemple si on ajoute ces deux points l'un après l'autre de la même manière que les autres points:
``` cpp
glm::vec3 point4 = glm::vec3(-0.5, -0.5, 0.0);
glm::vec3 point5 = glm::vec3(0.0, 0.0, 0.0);
```
On obtient successivement:

![Bezier Curve 4 points](https://github.com/Julian-Villeneuve/BezierCurve/blob/main/res/Bezier4points.png)

Puis:

![Bezier Curve 5 points](https://github.com/Julian-Villeneuve/BezierCurve/blob/main/res/Bezier5points.png)


## Bézier Patch

