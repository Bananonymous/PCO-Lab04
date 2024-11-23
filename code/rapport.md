# Laboratoire 04 : Gestion de ressources partagées

- Auteurs : Berberat Alex, Surbeck Léon


## Introduction au problème
Le but de ce laboratoire est de simuler la gestion de deux locomotives qui doivent passer sur un tronçon commun pour apprendre la gestion de ressources partagées.  
La première partie du laboratoire nous apprends à gérer les sections critique.  
La deuxième partie elle nous apprends à mettre des priorités sur des process qui ont besoin de ressources partagées.


## Choix d'implémentation

> [!Warning] A enlever quand rapport fini  
> Dans cette section, vous **décrivez** vos choix et votre logique pour résoudre le problème posé. Ce que nous attendons de vous, c'est une explication claire et concise. Nous ne voulons pas que vous copiez votre code dans le rapport en disant : "Voilà ce que j'ai fait." Aucun code ne doit apparaître dans ce rapport. Expliquez simplement vos choix, les raisonnements que vous avez suivis, etc.

### Programme 1
- `emergency_stop()`  
    Nous avons décidé de fixer la vitesse à 0 afin d'assurer que les locomotives ne puissent pas repartir.  
 

### Programme 2
Une grande parti du code a été copié collé depuis programme 1 comme indiqué par la consigne.  
Nous avons tout de même fait certaines adaptations.



## Tests effectués

> [!Warning] A enlever quand rapport fini  
> Les tests sont importants, ne les négligez pas. Le but d'un test n'est pas simplement de valider votre code dans un cas simple et de s'arrêter là. Il ne s'agit pas non plus de faire tourner votre programme de plus en plus longtemps. Réfléchissez aux moments potentiellement critiques de l'exécution du programme et cherchez à le faire planter ! C'est également ce que nous ferons lors de la correction. :)


Nous avons testé les locomotives avec différente vitesse afin de vérifier le bon fonctionnement. Nous avons constaté qu'avec une vitesse trop élevée l'inertie de la locomotive rendait son arrêt avant la section critique impossible.  

Nous avons aussi testé en changeant le point de départ des locomotives pour nous assurer que cela ne causait pas de problèmes.
