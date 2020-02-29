-- 计数器(用数码管显示，支持手动clk/秒表clk/暂停/复位 功能, 60进制) --
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity counter is
    port(
        clk: in std_logic;
        rst: in std_logic;
        pause: in std_logic;
        mode: in std_logic;--mode = '1'的时候是秒表，否则是手动加
        highcode: out std_logic_vector(6 downto 0);
        lowcode: out std_logic_vector(6 downto 0);
        outclk: out std_logic
    );
end counter;

architecture bhv of counter is
    component decoder
        port(
            bit_4_vec: in std_logic_vector(3 downto 0);
            bit_7_vec: out std_logic_vector(6 downto 0)
        );
    end component;
    component fourbitcounter
        port(
            clk: in std_logic;
            rst: in std_logic;
            pause: in std_logic;
            qvec: out std_logic_vector(3 downto 0)
        );
    end component;
    component clkpersecond
        port(
            clk: in std_logic;
            rst: in std_logic;
            clkps: out std_logic
        );
    end component;
    signal clockUsing: std_logic;
    signal clockPerSecond: std_logic;
    signal resetLow: std_logic := '0';
    signal resetHigh: std_logic := '0';
    signal outputLow: std_logic_vector(3 downto 0);
    signal outputHigh: std_logic_vector(3 downto 0);
begin
    clockUsing <= clockPerSecond when mode = '1' else 
        clk;
    resetLow <= '1' when outputLow = "1010" else --到10进1
        '0';
    resetHigh <= '1' when outputLow = "0000" and outputHigh = "0110" else --到60归零
        '0';
    outclk <= clockUsing;
    getclk: clkpersecond port map(clk=>clk, rst=>rst, clkps=>clockPerSecond);
    u1: fourbitcounter port map(clk=>clockUsing, rst=>(rst or resetLow), pause=>pause, qvec=>outputLow );
    u2: fourbitcounter port map(clk=>resetLow, rst=>(rst or resetHigh), pause=>pause, qvec=>outputHigh );
    decoder1: decoder port map(bit_4_vec=>outputLow, bit_7_vec=>lowcode);
    decoder2: decoder port map(bit_4_vec=>outputHigh, bit_7_vec=>highcode);
end bhv;
