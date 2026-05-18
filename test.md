# Instructions pour `init_coders()`

## Objectif

La fonction `init_coders()` doit préparer tous les coders de la simulation.

À la fin :
- tous les coders existent,
- tous leurs champs sont initialisés,
- les dongles gauche/droite sont correctement connectés.

---

# Structure mentale générale

```c
init_coders()
{
    boucle sur tous les coders
    {
        remplir les champs du coder
    }
}
```

---

# Étape 1 — Créer une boucle

Parcourir :

```c
sim->coders
```

jusqu’à :

```c
sim->number_of_coders
```

---

# Étape 2 — Donner un ID

Chaque coder doit avoir un identifiant unique.

Réfléchir à :
- `i`
- ou `i + 1`

pour avoir des IDs propres dans les logs.

---

# Étape 3 — Initialiser le compteur

Le coder vient d’être créé.

Donc :

```c
number_of_compiles_done
```

doit probablement commencer à :

```c
0
```

---

# Étape 4 — Stocker le pointeur vers la simulation

Chaque coder doit pouvoir accéder :
- aux timings,
- au stop flag plus tard,
- aux autres données globales.

Donc :

```c
coder->sim
```

doit pointer vers :

```c
sim
```

---

# Étape 5 — Connecter le dongle gauche

Pour un coder `i` :

le dongle gauche est probablement :

```c
sim->dongles[i]
```

---

# Étape 6 — Connecter le dongle droit

## Cas normal

Pour la plupart des coders :

```c
sim->dongles[i + 1]
```

---

## Cas spécial : dernier coder

Le dernier coder doit revenir au premier dongle.

Il faudra probablement utiliser :

```c
(i + 1) % sim->number_of_coders
```

pour créer le cercle.

---

# Étape 7 — Initialiser les timestamps

Tu peux :
- soit mettre `0`,
- soit utiliser le temps actuel plus tard.

Pas besoin de compliquer maintenant.

---

# Étape 8 — Ne PAS créer les threads maintenant

Cette fonction sert uniquement à :
- préparer les données,
- connecter les structures.

Pas encore :
- `pthread_create`
- mutex lock/unlock
- routine des coders

---

# À la fin de `init_coders()`

Chaque coder doit connaître :
- son ID
- sa simulation
- son dongle gauche
- son dongle droit

Et alors :
la simulation sera entièrement construite.
