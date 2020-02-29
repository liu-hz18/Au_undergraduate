--four-bit-adder with VHDL built-in adder, time loss: 9ns--
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity fouraddersys is
    port(
        a, b: in std_logic_vector(3 downto 0);
        cin: in std_logic;
        s: out std_logic_vector(3 downto 0);
        cout: out std_logic
    );
end fouraddersys;

architecture bhv of fouraddersys is
    signal sum: std_logic_vector(4 downto 0);
begin
    sum <= "00000" + a + b + cin;
    s <= sum(3 downto 0);
    cout <= sum(4);
end bhv;
