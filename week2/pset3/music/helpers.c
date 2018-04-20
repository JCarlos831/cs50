// Helper functions for music

#include <cs50.h>
#include <ctype.h>
#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // TODO
    int denominator;
    int eighths = 0;

    denominator = fraction[2];
    if (denominator == '8')
    {
        eighths = atoi(&fraction[0]);
        return eighths;
    }
    else if (denominator == '4')
    {
        eighths = (atoi(&fraction[0])) * 2;
        return eighths;
    }
    else if (denominator == '2')
    {
        eighths = (atoi(&fraction[0])) * 4;
        return eighths;
    }
    else if (denominator == '1')
    {
        eighths = (atoi(&fraction[0])) * 8;
        return eighths;
    }
    return 0;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    // TODO


    // Starting variable for frequency.  Made a double for more precision
    double f;

    // octave is the 2nd to last character in a string because \0 is last
    // if string is of length 2, then note is note[0] and octave is note[1] or strlen(note) - 1
    // if string is of lenght 3, then note is note[0], accidental is note[1], and octave is note[2] or strlen(note) - 1
    int octave = note[strlen(note) - 1];

    // Take Ascii value and convert to int value
    octave -= 48;


    // Check for note
    // A4 = 440hz --- semitone increase multiply by 2 1/12 power --- semitone decrease divide by 2 1/12 power
    if (note[0] == 'A')
    {
        f = 440.0;
    }
    else if (note[0] == 'B')
    {
        f = 440.0 * (pow(2.0, (2.0 / 12.0)));
    }
    else if (note[0] == 'C')
    {
        f = 440.0 / (pow(2.0, (9.0 / 12.0)));
    }
    else if (note[0] == 'D')
    {
        f = 440.0 / (pow(2.0, (7.0 / 12.0)));
    }
    else if (note[0] == 'E')
    {
        f = 440.0 / (pow(2.0, (5.0 / 12.0)));
    }
    else if (note[0] == 'F')
    {
        f = 440.0 / (pow(2.0, (4.0 / 12.0)));
    }
    else if (note[0] == 'G')
    {
        f = 440.0 / (pow(2.0, (2.0 / 12.0)));
    }


    // Account for accidentals
    if (note[1] == 'b')
    {
        f /= (pow(2.0, (1.0 / 12.0)));
    }
    else if (note[1] == '#')
    {
        f *= (pow(2.0, (1.0 / 12.0)));
    }

    // Jump up to next octave multiply by 2, go down to next octave divide by 2
    // Account for Octaves 5, 6, 7, 8
    if (octave > 4)
    {
        for (int i = 0; i < octave - 4; i++)
        {
            f *= 2.0;

        }
    }
    // Account for octave 0, 1, 2, 3
    else if (octave < 4)
    {
        for (int i = 0; i < 4 - octave; i++)
        {
            f /= 2.0;
        }
    }

    // Round frequency
    int freq = round(f);
    return freq;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // TODO
    if (s[0] == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
