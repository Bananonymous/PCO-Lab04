# Rapport du Laboratoire 04 : Gestion de Ressources Partagées

### Auteurs : Léon Surbeck, Alex Berberat

---

## Introduction

Le laboratoire 04 vise à explorer la gestion de ressources partagées et la résolution de compétitions entre processus, à l'aide de sémaphores. Pour ce faire, nous avons utilisé la simulation de maquette permettant la gestion de deux locomotives partageant un tronçon commun, avec des comportements distincts pour deux programmes :

1. **Programme 1** : Gestion de section critique avec inversion de direction périodique.
2. **Programme 2** : Ajout d'une gestion de priorité pour les accès au tronçon partagé.

---

## Choix d'implémentation

### Programme 1

- **Gestion du tronçon partagé** : 
  - Nous avons implémenté une classe `SharedSection` dérivée de l'interface `SharedSectionInterface`. Elle contrôle l'accès au tronçon critique à l'aide de sémaphores.
  - Une locomotive effectue une requête pour accéder au tronçon. Si celui-ci est occupé, elle s'arrête avant d'y entrer. Sinon, elle le traverse directement sans interruption.

- **Inversion de direction** : 
  - Chaque locomotive alterne sa direction après avoir complété un nombre fixe de tours, défini individuellement.
  - Une coordination est mise en place pour que les locomotives attendent à leur gare respective avant de repartir.

- **Arrêt d'urgence** : 
  - La méthode `emergency_stop()` force un arrêt immédiat en définissant la vitesse de toutes les locomotives à zéro, sans désactiver la maquette entière.

### Programme 2

- **Extension avec gestion de priorité** :
  - Nous avons introduit deux nouvelles fonctions, `request()` et `togglePriorityMode()`, pour gérer dynamiquement les priorités des locomotives.
  - Une locomotive formule une requête (contact 1) et obtient une réponse (contact 2) avant de traverser le tronçon partagé.
  - Les priorités sont inversées à chaque attente en gare, conformément aux exigences.

- **Arbitrage basé sur les priorités** :
  - La locomotive avec la priorité la plus élevée accède au tronçon en premier.
  - En cas de priorités égales, la première locomotive arrivée est servie.

---

## Tests effectués

1. **Validation des comportements** :
   - Vérification du respect des règles d'inversion de direction et des attentes en gare.
   - Simulation de vitesses variables pour tester les scénarios critiques, notamment les inerties trop élevées empêchant l'arrêt avant le tronçon partagé.

2. **Tests de robustesse** :
   - Introduction de conflits dans l'accès au tronçon partagé pour valider l'utilisation des sémaphores.
   - Simulation de défaillances comme des arrêts d'urgence successifs pour garantir une réponse fiable.

3. **Gestion des priorités (Programme 2)** :
   - Modification dynamique des priorités pour observer les changements de comportement des locomotives.
   - Validation que les locomotives respectent bien les nouvelles priorités après chaque attente en gare.

---

## Conclusion

Les deux programmes répondent aux objectifs fixés. Le Programme 1 établit une gestion de base des ressources partagées, tandis que le Programme 2 étend ces fonctionnalités avec un système de priorités dynamique. Les tests effectués garantissent une robustesse et un fonctionnement conforme aux attentes.
