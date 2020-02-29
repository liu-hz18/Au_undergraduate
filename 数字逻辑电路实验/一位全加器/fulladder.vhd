
--一位加法器(利用一位半加器实现)
--如果改成四位加法器，则需要超前进位

library ieee;
use ieee.std_logic_1164.all;

entity fulladder is
port(
    ain, bin, ci: in std_logic; --相当于参数和返回值
    s, co: out std_logic
);
end fulladder;

architecture arc of fulladder is
    component halfadder --元件描述语句
        port(
            a, b: in std_logic;
            so, co: out std_logic --端口名必须和源文件中实体中的端口命名保持一致
        );
    end component;
    signal s1, c1, c2: std_logic; --相当于内部变量
begin
    --构建端口map映射,从前者映射到后者，前者是component的端口名，后者为函数内部变量或参量
    u1: halfadder port map(a=>ain, b=>bin, so=>s1, co=>c1);
    u2: halfadder port map(a=>s1, b=>ci, so=>s, co=>c2);
    co <= c1 or c2;
end arc;
