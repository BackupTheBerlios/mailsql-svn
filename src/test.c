/* analyseur pour un langage de type Pascal */

%{
  /* besoin de ceci pour l’¡Çappel à atof() plus bas */
#include <math.h>
%}
MAIL	 ^[fF]rom:(.)*
CHIFFRE  [0-9]
ID       [a-z][a-z0-9]*
                                                                                
%%

{CHIFFRE}+  {
  printf( "Un entier : %s (%d)\n", yytext, atoi(yytext));
}

{CHIFFRE}+"."{CHIFFRE}* {
  printf( "Un nombre flottant : %s (%g)\n", yytext,
	  atof(yytext));
}

if|then|begin|end|procedure|function        {
  printf( "Un mot-clé : %s\n", yytext );
}
"[fF]rom:(.*)"	printf("1 mail de %s\n",yytext);

{ID}        printf( "Un identificateur : %s\n", yytext );

"+"|"-"|"*"|"/"   printf( "Un opérateur : %s\n", yytext );

"{"[^}\n]*"}"     /* manger les commentaires d’¡Çune ligne */

[ \t\n]+          /* manger les blancs */

.           printf( "Caractère non reconnu : %s\n", yytext );

%%

main(int argc,char** argv )
{
//++argv, --argc;  /* passer le nom du programme */
if ( argc > 1 )
     yyin = fopen( argv[0], "r" );
     else
     yyin = stdin;

yylex();
}
