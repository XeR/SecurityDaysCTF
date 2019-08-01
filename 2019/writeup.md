# writeups

Chaque épreuve contient un script permettant de prouver que l'épreuve est
réalisable.

## pwn1
Ce binaire est compilé sans protections. 
L'ordre des variables sur la pile est celui dont les variables sont déclarées.
On a donc:

```
+---------------+-----------+
| char name[64] | int admin |
+---------------+-----------+
```

Quand on rentre un nom trop gros (plus de 64 caractères), la variable `admin`
est modifiée, et le binaire nous affiche le flag


## pwn2
Ce binaire est légèrement différent: l'overflow se trouve dans une fonction
différente. Si on dépasse le buffer, on va d'abord réecrire l'adresse de retour
de la fonction.

La solution attendue est de modifier l'adresse de retour pour pointer au milieu
de la fonction `main`, juste avant l'appel à `system("cat flag")`.


## pwn3
Ce binaire est vulnérable à une format string. Pour simplifier l'exploitation,
la variable à modifier est dans une variable globale. Son adresse ne change pas.

La solution attendue est d'utiliser `%n` pour ecrire n'importe quoi dans
`admin`. L'adresse contient des NULL byte et doit donc être à la fin de la
chaîne. (Sinon `printf` n'ira pas lire le reste)

Attention : sur musl libc, les formats de positions (`%42$d`) ne **fonctionnent
pas**. Il faut donc faire plusieurs `%d` à la suite pour avancer le pointeur.


## pwn4
Ce binaire a plusieurs protections: stack NX et canary. Le code contient une
fonction déclarée dans une autre fonction, ce qui a pour effet de réactiver le
NX.

La vulnérabilité est qu'il n'y a pas de vérification sur l'indice du tableau.
Pour exploiter ce binaire, il faut écrire son shellcode dans la variable
`array`, lire après le tableau pour trouver la valeur sauvée de rbp (qui
contient un pointeur sur la pile), et modifier l'adresse de retour qui se trouve
juste après pour pointer sur le shellcode. (On peut faire un nop sled)


## pwn5
Ce binaire a toutes sortes de protections récentes. Il lit une chaîne et
l'affiche en boucle.

On peut lire le canary en envoyant une chaîne ayant pile la bonne taille. On
peut egalement recuperer l'adresse de retour qui se trouve dans
`__libc_start_main` de la libc.

Attention : sur musl libc, le premier byte du canary n'est pas 0!

Une fois ces deux infos obtenues, il suffit de faire une ROP chain avec trois
gadgets de la libc:
- pop rdi
- "/bin/sh"
- system
