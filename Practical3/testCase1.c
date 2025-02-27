/* salary calculation */
void main()
{
    long int bs, da, hra, gs;
    // take basic salary as input
    scanf("%ld", &bs);
    // calculate allowances
    da = bs * 0.20;
    hra = bs * 0.40;
    gs = bs + da + hra;
    // display salary slip
    printf("\nbs : %ld", bs);
    printf("\nda : %ld", da);
    printf("\nhra : %ld", hra);
    printf("\ngs : %ld", gs);
}
