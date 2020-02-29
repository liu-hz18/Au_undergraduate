-- 产生秒表序列(时钟频率1MHz: 产生1s的周期序列) --
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity clkpersecond is
    port(
        clk: in std_logic;
        rst: in std_logic;
        clkps: out std_logic
    );
end clkpersecond;

architecture bhv of clkpersecond is
    signal outclk: std_logic := '0';
    signal count: integer := 0;
    constant freq: integer := 1000000/2;--设置时钟频率1MHz
begin
    clkps <= outclk;
    process(clk, rst)
    begin
        if rst = '1' then
            count <= 0;
            outclk <= '0';
        elsif clk'event and clk='1' then
            if count < freq then
                count <= count + 1;
            else
                count <= 0;
                outclk <= (not outclk);--跳变
            end if;
        end if;
    end process;
end bhv;