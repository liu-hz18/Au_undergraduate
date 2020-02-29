-- 四位加法计数器 --
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity fourbitcounter is
    port(
        clk: in std_logic;
        rst: in std_logic;
        pause: in std_logic;
        qvec: out std_logic_vector(3 downto 0)
    );
end fourbitcounter;

architecture bhv of fourbitcounter is
    component d_ff
        port(
            clk: in std_logic;
            rst: in std_logic;
            pause: in std_logic;
            d: in std_logic;
            q: out std_logic;
            nq: out std_logic
        );
    end component;
    signal q_buf: std_logic_vector(3 downto 0);
    signal nq_buf: std_logic_vector(3 downto 0);
begin
    u0: d_ff port map(clk=>clk, rst=>rst, pause=>pause, d=>nq_buf(0), q=>q_buf(0), nq=>nq_buf(0) );
    u1: d_ff port map(clk=>nq_buf(0), rst=>rst, pause=>pause, d=>nq_buf(1), q=>q_buf(1), nq=>nq_buf(1) );
    u2: d_ff port map(clk=>nq_buf(1), rst=>rst, pause=>pause, d=>nq_buf(2), q=>q_buf(2), nq=>nq_buf(2) );
    u3: d_ff port map(clk=>nq_buf(2), rst=>rst, pause=>pause, d=>nq_buf(3), q=>q_buf(3), nq=>nq_buf(3) );
    qvec <= q_buf;
end bhv;
