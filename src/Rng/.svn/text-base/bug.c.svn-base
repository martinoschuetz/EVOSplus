#include <stdio.h>


static double rand;

double
randomperc ()		/* "Zufalls"zahl aus ]0.0..1.0[ */
{
  rand += 0.1;
  return ((double) rand);
}

int
rnd (lo, hi)
     int lo, hi;
{
  return ((int) (randomperc () * (hi + 1 - lo) + lo));
}

int
rnd_Fritz (lo, hi)
     int lo, hi;
{
  return ((int) (randomperc () * (hi - lo) + lo));
}

int
rnd_Hugo (lo, hi)
     int lo, hi;
{
  return ((int) (randomperc () * (lo - 1) ));
}

double
rnd_double (lo, hi)
     double lo, hi;
{
  return ((double) (randomperc () * (hi + 1.0 - lo) + lo));
}

double
rnd_Fritz_double (lo, hi)
     double lo, hi;
{
  return ((double) (randomperc () * (hi - lo) + lo));
}

double
rnd_Hugo_double (lo, hi)
     double lo, hi;
{
  return ((double) (randomperc () * (hi - lo - 1) + lo));
}

void
main (argc, argv)
     int argc;
     char *argv;
{
  int i, positionvalue;

  rand = 0.0;
  for (i = 0; i < 9; i++)
    printf ("%d %d (rand=%g)\n", i, rnd_Fritz (0, 1), rand);
  printf ("\n");

  rand = 0.0;
  for (i = 0; i < 9; i++)
    printf ("%d %d (rand=%g)\n", i, rnd (0, 1), rand);
  printf ("(+1)\n\n");

  rand = 0.0;
  for (i = 0; i < 9; i++)
    printf ("%d %d (rand=%g)\n", i, rnd_Fritz (-5, 5), rand);
  printf ("\n");

  rand = 0.0;
  for (i = 0; i < 9; i++)
    printf ("%d %d (rand=%g)\n", i, rnd (-5, 5), rand);
  printf ("(+1)\n\n");

  rand = 0.0;
  for (i = 0; i < 9; i++)
    printf ("%d %d (rand=%g)\n", i, rnd_Fritz (0, 2), rand);
  printf ("\n");

  rand = 0.0;
  for (i = 0; i < 9; i++)
    printf ("%d %d (rand=%g)\n", i, rnd (0, 2), rand);
  printf ("(+1)\n\n");

  rand = 0.0;
  for (i = 0; i < 9; i++)
    printf ("%d %d (rand=%g)\n", i, rnd_Fritz (-2, 0), rand);
  printf ("\n");

  rand = 0.0;
  for (i = 0; i < 9; i++)
    printf ("%d %d (rand=%g)\n", i, rnd (-2, 0), rand);
  printf ("(+1)\n\n");

  rand = 0.0;
  for (i = 0; i < 9; i++)
    printf ("%d %d (rand=%g)\n", i, rnd_Hugo (-2, 0), rand);
  printf ("(-1)\n\n");

  rand = 0.0;
  for (i = 0; i < 9; i++)
    printf ("%d %g (rand=%g)\n", i, rnd_Fritz_double(-10.0, 0.0), rand);
  printf ("\n");

/*  rand = 0.0;
  for (i = 0; i < 9; i++)
    printf ("%d %g (rand=%g)\n", i, rnd_Fritz_double(0.0, 1.0), rand);
  printf ("\n");

  rand = 0.0;
  for (i = 0; i < 9; i++)
    printf ("%d %g (rand=%g)\n", i, rnd_double(0.0, 1.0), rand);
  printf ("(+1.0)\n\n");

  rand = 0.0;
  for (i = 0; i < 9; i++)
    printf ("%d %g (rand=%g)\n", i, rnd_Fritz_double(-5.0, 5.0), rand);
  printf ("\n");

  rand = 0.0;
  for (i = 0; i < 9; i++)
    printf ("%d %g (rand=%g)\n", i, rnd_double(-5.0, 5.0), rand);
  printf ("(+1.0)\n\n");

  for (positionvalue = -1; positionvalue < 2; positionvalue++)
    {
      rand = 0.0;
      for (i = 0; i < 9; i++)
	printf ("%d flip %d to %d (rand=%g)\n", i, positionvalue,
		(positionvalue + rnd_Fritz (1, 2) + 1) % 3 - 1, rand);
    }
  printf (":-(\n\n");

  for (positionvalue = -1; positionvalue < 2; positionvalue++)
    {
      rand = 0.0;
      for (i = 0; i < 9; i++)
	printf ("%d flip %d to %d (rand=%g)\n", i, positionvalue,
		(positionvalue + rnd (1, 2) + 1) % 3 - 1, rand);
    }
  printf (":-)\n");
*/
}
