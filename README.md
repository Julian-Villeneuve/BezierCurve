# Projet M1 IAFA - Informatique Graphique

### Mesh
La classe Mesh est la classe la plus utilisée du projet, servant à construire le maillage des courbes et surfaces de Bézier.

### Bézier Curve

Pour l'instant il faut ajouter les points de contrôle à la main, la méthode d'ajout en temps réel avec la souris n'est pas fonctionnelle (ce sera avec un clique gauche,
cela n'ajoute que des points tous seuls pour le moment).
Dans la méthode initializeGL() de la classe OpenGLWidget, on doit ajouter les points dans 3 listes différentes:
- La liste de points de la classe Point, affichant simplement les points:
```	cpp
_points = new Points();
_points->Add(glm::vec2(0.5, -0.5));
_points->Add(glm::vec2(0.5, 0.5));
_points->Add(glm::vec2(-0.5, 0.5));
```
- La liste de ces mêmes points dans un vecteur qui les enverra dans la classe Curve, qui calculera la courbe de Bézier résultante et la dessinera:
``` cpp
_pointsListCurve.push_back(glm::vec3(0.5, -0.5, 0));
_pointsListCurve.push_back(glm::vec3(0.5, 0.5, 0));
_pointsListCurve.push_back(glm::vec3(-0.5, 0.5, 0));
```
- Toujours ces mêmes points, dans un vecteur de Vertex qui en soit fait doublon mais que j'ai séparé pour bien distinguer le polygone de la courbe:
``` cpp
struct Vertex v1, v2, v3, v4, v5;
v1.pos = glm::vec3(0.5, -0.5, 0);
v2.pos = glm::vec3(0.5, 0.5, 0);
v3.pos = glm::vec3(-0.5, 0.5, 0);
v4.pos = glm::vec3(-0.5, -0.5, 0);
v5.pos = glm::vec3(0, 0, 0);
controlVertices.push_back(v1);
controlVertices.push_back(v2);
controlVertices.push_back(v3);
controlVertices.push_back(v4);
controlVertices.push_back(v5);
```
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
glm::vec3(-0.5, -0.5, 0);
glm::vec3(0, 0, 0);
```
On obtient successivement:

![Bezier Curve 4 points](https://github.com/Julian-Villeneuve/BezierCurve/blob/main/res/Bezier4points.png)

Puis:

![Bezier Curve 5 points](https://github.com/Julian-Villeneuve/BezierCurve/blob/main/res/Bezier5points.png)


### Bézier Patch

