string cypher(string text, int k)
{
   string new_text[strlen(text)];
   for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isupper(text[i]))
        {
            printf("%s", text[i + k]);
        }
        else if (islower(text[i]))
        {
            printf("%s", text[i + k]);
        }
        else
        {
            printf("%s", text[i]);
        }
    }

}

string cypher(string text, int k)
{
   string new_text[strlen(text)];
   for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isupper(text[i]))
        {
            new_text[i] = text[i + k];
        }
        else if (islower(text[i]))
        {
            new_text[i] = text[i + k];
        }
        else
        {
            new_text[i] = text[i];
        }
    }
    return new_text;
}

