start: hello.beam
	$(info Run: hello:start(4040). in repl)
	#erl hello.beam
	#erl -s hello start 4040 -s erlang halt -noshell hello.beam
	erl -s hello start 4040 -noshell hello.beam
#-pa ./ebin -s lfe_comp file blub.lfe -s blub usage -s erlang halt -noshell

hello.beam:
	erlc hello.erl
