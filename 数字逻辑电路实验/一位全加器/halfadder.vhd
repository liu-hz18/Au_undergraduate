
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;

entity halfadder is
port(
    a, b: in std_logic;
    so, co: out std_logic
);
end halfadder;

architecture rt1 of halfadder is
begin 
    co <= a and b; --两个语句是并列执行的，不能利用上面的变量为下面的变量赋值
    so <= a xor b;
end rt1;
