%%%
%%% A simple "Hello, world" server in the Erlang.
%%%

-module(hello_erlang).
-export([
           main/1,
           run_server/0,
           start/0
         ]).

main(_) ->
  start(),
  receive
  stop -> ok
          end.

run_server() ->
  ok = inets:start(),
  {ok, _} = inets:start(httpd, [
                          {port, 8080},
                          {server_name, "hello_erlang"},
                          {server_root, "/tmp"},
                          {document_root, "/tmp"},
                          {bind_address, "localhost"}
                        ]).

start() -> run_server().
