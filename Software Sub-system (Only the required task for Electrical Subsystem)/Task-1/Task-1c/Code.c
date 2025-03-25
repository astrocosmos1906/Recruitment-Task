bool judgeCircle(char *moves)
{
    int horizontal = 0;
    int vertical = 0;
    
    for (int i = 0; moves[i] != '\0'; i++) 
    {
        switch (moves[i]) 
        {
            case 'R': 
            horizontal++; 
            break;

            case 'L': 
            horizontal--; 
            break;

            case 'U': 
            vertical++; 
            break;

            case 'D': 
            vertical--; 
            break;
        }
    }
    return (horizontal == 0 && vertical == 0);
}
