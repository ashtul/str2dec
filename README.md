# String to Decimal
str2dec is a function that receives a string representing a number as an input and has two integers as out-params.
* `num`  - the integer representation of the string value
* `expo` - the exponent of the string value
a numeric representation is **num *  10<sup>-expo</sup>**

# Test

Compile test: `gcc str2dec.c test.c -o str2dec`

```sql
Run: `./str2dec 1234 +12.34 0.01234 -1.234E3 -1.234E+3 -1.234E-3`

Results:
num 1234         expo 0
num 1234         expo 2
num 1234         expo 5
num -1234        expo 0
num -1234        expo 0
num -1234        expo 6
```