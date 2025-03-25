bool isValid(char *s) 
{
    int i = 0, j = 0;
    char c;

    int round = 0;
    int curly = 0;
    int square = 0;

    while ((c = s[i]) != '\0') 
    {
        if (c == '(') 
        {
            round++;
        }

        else if (c == ')') 
        {
            if (round == 0) return false;
            round--;
        } 
        
        else if (c == '{') 
        {
            curly++;
        }

        else if (c == '}') 
        {
            if (curly == 0) return false;
            curly--;
        } 
        
        else if (c == '[') 
        {
            square++;
        }

        else if (c == ']') 
        {
            if (square == 0) return false;
            square--;
        }
        i++;
    }
    return (round == 0 && curly == 0 && square == 0);
}
