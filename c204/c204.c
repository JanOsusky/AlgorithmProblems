/* ******************************* c204.c *********************************** */
/*  Předmět: Algoritmy (IAL) - FIT VUT v Brně                                 */
/*  Úkol: c204 - Převod infixového výrazu na postfixový (s využitím c202)     */
/*  Referenční implementace: Petr Přikryl, listopad 1994                      */
/*  Přepis do jazyka C: Lukáš Maršík, prosinec 2012                           */
/*  Upravil: Kamil Jeřábek, září 2019                                         */
/*           Daniel Dolejška, září 2021                                       */
/*  Implementoval: Jan Osuský                                                 */
/* ************************************************************************** */
/*
** Implementujte proceduru pro převod infixového zápisu matematického výrazu
** do postfixového tvaru. Pro převod využijte zásobník (Stack), který byl
** implementován v rámci příkladu c202. Bez správného vyřešení příkladu c202
** se o řešení tohoto příkladu nepokoušejte.
**
** Implementujte následující funkci:
**
**    infix2postfix ... konverzní funkce pro převod infixového výrazu
**                      na postfixový
**
** Pro lepší přehlednost kódu implementujte následující pomocné funkce:
**
**    untilLeftPar ... vyprázdnění zásobníku až po levou závorku
**    doOperation .... zpracování operátoru konvertovaného výrazu
**
** Své řešení účelně komentujte.
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako procedury
** (v jazyce C procedurám odpovídají funkce vracející typ void).
**
**/

#include "c204.h"

bool solved;

/**
 * Pomocná funkce untilLeftPar.
 * Slouží k vyprázdnění zásobníku až po levou závorku, přičemž levá závorka bude
 * také odstraněna.
 * Pokud je zásobník prázdný, provádění funkce se ukončí.
 *
 * Operátory odstraňované ze zásobníku postupně vkládejte do výstupního pole
 * znaků postfixExpression.
 * Délka převedeného výrazu a též ukazatel na první volné místo, na které se má
 * zapisovat, představuje parametr postfixExpressionLength.
 *
 * Aby se minimalizoval počet přístupů ke struktuře zásobníku, můžete zde
 * nadeklarovat a používat pomocnou proměnnou typu char.
 *
 * @param stack Ukazatel na inicializovanou strukturu zásobníku
 * @param postfixExpression Znakový řetězec obsahující výsledný postfixový výraz
 * @param postfixExpressionLength Ukazatel na aktuální délku výsledného postfixového výrazu
 */
void untilLeftPar(Stack *stack, char *postfixExpression, unsigned *postfixExpressionLength)
{
	char *currentChar = (char *)malloc(sizeof(char)); // help variable
	if (currentChar == NULL)
		printf("help char variable allocation error!\n");
	while (!Stack_IsEmpty(stack)) // checking that stack is not empty
	{
		Stack_Top(stack, currentChar); // putting char from top to currentChar
		Stack_Pop(stack);			   // removing char from stack
		if (*currentChar != '(')
		{
			postfixExpression[*postfixExpressionLength] = *currentChar; // inserting char to array
			(*postfixExpressionLength)++;								// increasing number of chars
		}
		else
		{
			break;
		}
	}
}

/**
 * Pomocná funkce doOperation.
 * Zpracuje operátor, který je předán parametrem c po načtení znaku ze
 * vstupního pole znaků.
 *
 * Dle priority předaného operátoru a případně priority operátoru na vrcholu
 * zásobníku rozhodneme o dalším postupu.
 * Délka převedeného výrazu a taktéž ukazatel na první volné místo, do kterého
 * se má zapisovat, představuje parametr postfixExpressionLength, výstupním
 * polem znaků je opět postfixExpression.
 *
 * @param stack Ukazatel na inicializovanou strukturu zásobníku
 * @param c Znak operátoru ve výrazu
 * @param postfixExpression Znakový řetězec obsahující výsledný postfixový výraz
 * @param postfixExpressionLength Ukazatel na aktuální délku výsledného postfixového výrazu
 */
void doOperation(Stack *stack, char c, char *postfixExpression, unsigned *postfixExpressionLength)
{
	char topOp;
	while ((stack->topIndex != -1) && (stack->array[stack->topIndex] != '(') && !((stack->array[stack->topIndex] == '+' || stack->array[stack->topIndex] == '-') && (c == '*' || c == '/')))
	{ // nothing in stack;           left bracket means we can add the operator to the stack;         lower value operator on top of the stack, we can add the operator;
		Stack_Top(stack, &topOp);
		postfixExpression[*postfixExpressionLength] = topOp;
		(*postfixExpressionLength)++;
		Stack_Pop(stack);
	}
	Stack_Push(stack, c);
	return;

	// while (!Stack_IsEmpty(stack)) // going thought the stack
	//{
	//	char *currentChar;
	//	Stack_Top(stack, currentChar);
	//
	//	if (*currentChar == '(')
	//	{
	//		break; // on top of the stack is left bracket
	//	}
	//
	//	if ((*currentChar == '+' || *currentChar == '-') && (c == '*' || c == '/'))
	//	{
	//		break; // On top of the stack is operator with lower priority
	//	}
	//
	//	postfixExpression[*postfixExpressionLength] = *currentChar;
	//	postfixExpressionLength++; // mozna musi byt *
	//	Stack_Pop(stack);
	//}
	//
	// Stack_Push(stack, c); // inserting operatator to top of the stack
}

/**
 * Konverzní funkce infix2postfix.
 * Čte infixový výraz ze vstupního řetězce infixExpression a generuje
 * odpovídající postfixový výraz do výstupního řetězce (postup převodu hledejte
 * v přednáškách nebo ve studijní opoře).
 * Paměť pro výstupní řetězec (o velikosti MAX_LEN) je třeba alokovat. Volající
 * funkce, tedy příjemce konvertovaného řetězce, zajistí korektní uvolnění zde
 * alokované paměti.
 *
 * Tvar výrazu:
 * 1. Výraz obsahuje operátory + - * / ve významu sčítání, odčítání,
 *    násobení a dělení. Sčítání má stejnou prioritu jako odčítání,
 *    násobení má stejnou prioritu jako dělení. Priorita násobení je
 *    větší než priorita sčítání. Všechny operátory jsou binární
 *    (neuvažujte unární mínus).
 *
 * 2. Hodnoty ve výrazu jsou reprezentovány jednoznakovými identifikátory
 *    a číslicemi - 0..9, a..z, A..Z (velikost písmen se rozlišuje).
 *
 * 3. Ve výrazu může být použit předem neurčený počet dvojic kulatých
 *    závorek. Uvažujte, že vstupní výraz je zapsán správně (neošetřujte
 *    chybné zadání výrazu).
 *
 * 4. Každý korektně zapsaný výraz (infixový i postfixový) musí být uzavřen
 *    ukončovacím znakem '='.
 *
 * 5. Při stejné prioritě operátorů se výraz vyhodnocuje zleva doprava.
 *
 * Poznámky k implementaci
 * -----------------------
 * Jako zásobník použijte zásobník znaků Stack implementovaný v příkladu c202.
 * Pro práci se zásobníkem pak používejte výhradně operace z jeho rozhraní.
 *
 * Při implementaci využijte pomocné funkce untilLeftPar a doOperation.
 *
 * Řetězcem (infixového a postfixového výrazu) je zde myšleno pole znaků typu
 * char, jenž je korektně ukončeno nulovým znakem dle zvyklostí jazyka C.
 *
 * Na vstupu očekávejte pouze korektně zapsané a ukončené výrazy. Jejich délka
 * nepřesáhne MAX_LEN-1 (MAX_LEN i s nulovým znakem) a tedy i výsledný výraz
 * by se měl vejít do alokovaného pole. Po alokaci dynamické paměti si vždycky
 * ověřte, že se alokace skutečně zdrařila. V případě chyby alokace vraťte namísto
 * řetězce konstantu NULL.
 *
 * @param infixExpression vstupní znakový řetězec obsahující infixový výraz k převedení
 *
 * @returns znakový řetězec obsahující výsledný postfixový výraz
 */
char *infix2postfix(const char *infixExpression)
{
	char *postfixExpression = (char *)malloc(MAX_LEN * sizeof(char));
	if (postfixExpression == NULL)
	{
		return NULL; // malloc failed
	}
	Stack *stack = (Stack *)malloc(sizeof(Stack));
	if (stack == NULL)
	{
		free(postfixExpression); // malloc failed but we already have postfixExpresion allocated
		return NULL;
	}
	Stack_Init(stack);
	unsigned zero = 0;
	unsigned *postfixExpressionLength = &zero;
	for (int i = 0; infixExpression[i] != '\0'; i++)
	{
		if ((infixExpression[i] >= '0' && infixExpression[i] <= '9') || (infixExpression[i] >= 'a' && infixExpression[i] <= 'z') || (infixExpression[i] >= 'A' && infixExpression[i] <= 'Z'))
		{ // if its not a operator or parentesis put it to result
			postfixExpression[*postfixExpressionLength] = infixExpression[i];
			(*postfixExpressionLength)++;
		}
		if (infixExpression[i] == '*' || infixExpression[i] == '/' || infixExpression[i] == '+' || infixExpression[i] == '-')
		{
			doOperation(stack, infixExpression[i], postfixExpression, postfixExpressionLength); // handling operators
		}
		if (infixExpression[i] == ')')
		{
			untilLeftPar(stack, postfixExpression, postfixExpressionLength); // handling end of parenthesis expression
		}
		if (infixExpression[i] == '(') // start of parenthesis expression
		{
			Stack_Push(stack, infixExpression[i]);
		}
		if (infixExpression[i] == '=') // end of a expression
		{
			while (!Stack_IsEmpty(stack)) // adding the rest of the operators to the expresion
			{
				char topOp;
				Stack_Top(stack, &topOp);
				postfixExpression[*postfixExpressionLength] = topOp;
				(*postfixExpressionLength)++;
				Stack_Pop(stack);
			}
			// was not increased because it didnt go in other functions
			postfixExpression[*postfixExpressionLength] = '='; // adding =
			(*postfixExpressionLength)++;
			break;
		}
	}

	postfixExpression[*postfixExpressionLength] = '\0'; // adding \0
	free(stack);

	return postfixExpression; // returning infix expresion
}

/** .
 * Pomocná metoda pro vložení celočíselné hodnoty na zásobník.
 *
 * Použitá implementace zásobníku aktuálně umožňuje vkládání pouze
 * hodnot o velikosti jednoho byte (char). Využijte této metody
 * k rozdělení a postupné vložení celočíselné (čtyřbytové) hodnoty
 * na vrchol poskytnutého zásobníku.
 *
 * @param stack ukazatel na inicializovanou strukturu zásobníku
 * @param value hodnota k vložení na zásobník
 */
void expr_value_push(Stack *stack, int value)
{
	char c;
	for (int i = 0; i < 3; i++)
	{
		c = (char)((value >> 8 * (3 - i)) & 0xFF);
		Stack_Push(stack, c);
	}
	c = (char)(value & 0xFF);
	Stack_Push(stack, c);
}

/**
 * Pomocná metoda pro extrakci celočíselné hodnoty ze zásobníku.
 *
 * Využijte této metody k opětovnému načtení a složení celočíselné
 * hodnoty z aktuálního vrcholu poskytnutého zásobníku. Implementujte
 * tedy algoritmus opačný k algoritmu použitému v metodě
 * `expr_value_push`.
 *
 * @param stack ukazatel na inicializovanou strukturu zásobníku
 * @param value ukazatel na celočíselnou proměnnou pro uložení
 *   výsledné celočíselné hodnoty z vrcholu zásobníku
 */
void expr_value_pop(Stack *stack, int *value)
{
	*value = 0;
	for (size_t i = 0; i < sizeof(int); i++)
	{
		char c;
		Stack_Top(stack, &c);
		Stack_Pop(stack);
		// shifting to the right position
		*value |= (c << (i * 8));
	}
}

/**
 * Tato metoda provede vyhodnocení výrazu zadaném v `infixExpression`,
 * kde hodnoty proměnných použitých v daném výrazu jsou definovány
 * v poli `variableValues`.
 *
 * K vyhodnocení vstupního výrazu využijte implementaci zásobníku
 * ze cvičení c202. Dále také využijte pomocných funkcí `expr_value_push`,
 * respektive `expr_value_pop`. Při řešení si 	můžete definovat libovolné
 * množství vlastních pomocných funkcí.
 *
 * Předpokládejte, že hodnoty budou vždy definovány
 * pro všechy proměnné použité ve vstupním výrazu.
 *
 * @param infixExpression vstpní infixový výraz s proměnnými
 * @param variableValues hodnoty proměnných ze vstupního výrazu
 * @param variableValueCount počet hodnot (unikátních proměnných
 *   ve vstupním výrazu)
 * @param value ukazatel na celočíselnou proměnnou pro uložení
 *   výsledné hodnoty vyhodnocení vstupního výrazu
 *
 * @return výsledek vyhodnocení daného výrazu na základě poskytnutých hodnot proměnných
 */
bool eval(const char *infixExpression, VariableValue variableValues[], int variableValueCount, int *value)
{
	Stack *stack = (Stack *)malloc(sizeof(Stack));
	Stack_Init(stack);
	char *postfixExpression;
	postfixExpression = infix2postfix(infixExpression); // solving the operators problems and brackets
	int position = 0;
	for (int i = 0; i != '='; i++)
	{
		if (position < variableValueCount)
		{
			VariableValue var = variableValues[position];
			if (var.name == postfixExpression[i])
			{
				expr_value_push(stack, var.value);
				position++;
			}
		}
		if (postfixExpression[i] == '*' || postfixExpression[i] == '/' || postfixExpression[i] == '+' || postfixExpression[i] == '-')
		{
			int operand2 = 0;
			expr_value_pop(stack, &operand2);
			int operand1 = 0;
			expr_value_pop(stack, &operand1);

			switch (postfixExpression[i]) // deciding with operation to apply
			{
			case '+':
				expr_value_push(stack, operand1 + operand2);
				break;
			case '-':
				expr_value_push(stack, operand1 - operand2);
				break;
			case '*':
				expr_value_push(stack, operand1 * operand2);
				break;
			case '/':
				expr_value_push(stack, operand1 / operand2);
				break;
			}
		}
	}
	expr_value_pop(stack, value); // putting the result to *value
	return true;
}

/* Konec c204.c */
