<?php

	include_once("geshi.php");

	$geshi =& new GeSHI("main = {
	
	init = function()
	
		-- Images
		player.image = game:addImage('img_player', 'img/player.gif');
		enemy.image = game:addImage('img_enemy', 'img/enemy.gif');
		
		for i=1, num_enemies do
			enemies[i] = enemy:new();
			enemies[i].y = -math.random(5000) - 200;
			enemies[i].x = math.random(1000) + 100;
		end
		
	end,
	
	update = function(dt)
	
		local thrust = 500;

		if keyboard:isDown(LOVE_KEY_RIGHT) then
			player1.xspeed = player1.xspeed + (thrust * dt);
		end
		
		if keyboard:isDown(LOVE_KEY_LEFT) then		
			player1.xspeed = player1.xspeed - (thrust * dt);
		end
		
		if keyboard:isDown(LOVE_KEY_UP) then		
			player1.yspeed = player1.yspeed - (thrust * dt);
		end
		
		if keyboard:isDown(LOVE_KEY_DOWN) then		
			player1.yspeed = player1.yspeed + (thrust * dt);
		end
		
		-- Move player
		player1.x = player1.x + (dt * player1.xspeed);
		player1.y = player1.y + (dt * player1.yspeed);	
		
		for i=1, num_enemies do
		
			if enemies[i].y < 1200 then
				enemies[i].y = enemies[i].y + 200 * dt;
			else
				enemies[i].y = -200;
			end
		end
	
	end,
	
	render = function()
	
		player1:render();

		for i=1, num_enemies do
			enemies[i]:render();
		end

	
	end", "lua");
	
	$geshi->set_header_type(GESHI_HEADER_NONE);
	
	$geshi->set_keyword_group_style(1, 'color: #1f6ed9; font-weight: bold;', true);
	$geshi->set_comments_style(1, 'color: #4db12a;', true);
	$geshi->set_brackets_style('color: #1f6ed9;');
	$geshi->set_numbers_style('color: #358917;');
	$geshi->set_strings_style('color: #a31515;');
	
	$geshi->add_keyword_group(10, 'color: #666; font-weight: bold;', false, array(
		'main', 'init', 'update', 'render', 
		'keyboard:isDown',
		'mouse:getX','mouse:getY',
		'game:addImage'));
		
	$geshi->set_url_for_keyword_group(10, "?page=documentation&amp;lookup={FNAME}");
		
	$geshi->set_tab_width(3);

?>

<div class="title">
	Tutorial Demo
</div>

<div class="tutorial">


<div class="ss_box" style="float: right;">
     <div class="top"><!-- --></div>
     <div class="image_info_inactive" onmouseover="ssOver(this)" onmouseout="ssOut(this)">
          <div class="title">Particle Emission</div>
     </div>
     <img src="gfx/ss_particles.png" alt="Particles Screenshot" />
     <div class="caption">
          Fig. 1. Some *hot* particle emission.
     </div>
     <div class="bot"><!-- --></div>
</div>


Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Phasellus vulputate adipiscing lacus. Quisque tristique. Aliquam eget lectus id augue fermentum nonummy. Proin nec eros non nulla facilisis tincidunt. Cras lobortis. Aenean ligula. Suspendisse potenti. Aenean posuere sodales erat. Donec non nisi. Morbi ut est sit amet neque laoreet tincidunt. Integer dapibus pretium justo. Suspendisse risus. Suspendisse potenti. Praesent fringilla quam ut lacus. 
<br /><br />
In molestie auctor elit. Aenean sagittis, tellus vel hendrerit tempus, dolor augue nonummy ipsum, non placerat purus elit quis enim. Mauris leo. Donec blandit metus. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Nam posuere, magna in pulvinar tincidunt, mi dolor congue elit, at tempor dui ligula sed lectus. Vivamus orci orci, convallis vitae, pellentesque accumsan, interdum in, sapien. Phasellus ac mauris. Maecenas venenatis odio non nisl. Aliquam leo tortor, ullamcorper et, placerat ut, ultricies at, lacus.
<br /><br />
Donec vitae orci. Fusce non tellus. Nulla sem ante, pharetra eu, hendrerit quis, ultricies in, tellus. Pellentesque sed velit eu augue varius fringilla. Maecenas eget lacus. Mauris ultrices mauris et turpis. Vestibulum elit. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Nullam ligula urna, porttitor et, hendrerit sed, iaculis posuere, sapien. Quisque tincidunt, nibh quis feugiat dapibus, justo eros scelerisque felis, vel laoreet elit risus a lorem. Aenean nonummy lorem aliquam tellus tristique consectetuer. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Suspendisse sem massa, lobortis id, fringilla non, blandit a, ligula. 
<div class="code">
<div class="header">
	From: <span class="filename">entry.lua</span>
</div>
<div class="content">
	<code>
	<?php
	
		echo $geshi->parse_code();
	
	?>
	</code>
</div>
</div>
Sed viverra magna a nulla. Proin varius felis quis augue. Vestibulum sit amet elit non metus iaculis consequat. Donec mattis interdum elit. Aliquam tristique. In hac habitasse platea dictumst. Phasellus vehicula fermentum leo. Etiam dignissim scelerisque massa. Quisque pellentesque. Praesent porta consectetuer tortor. Proin tempor, mauris non adipiscing feugiat, lorem mauris scelerisque dui, quis fermentum quam diam id massa. Ut leo. Proin bibendum est molestie turpis. 
<br /><br />
Proin vitae felis eu lacus ornare faucibus. Integer blandit urna ac nunc. Donec porta tempus leo. Donec urna justo, molestie at, hendrerit vestibulum, pretium eu, neque. Phasellus ac mauris a purus lacinia consequat. Nullam fermentum justo eget lorem. Nullam magna tellus, gravida a, vehicula ac, pulvinar vel, nisl. Aenean fermentum ullamcorper purus. Maecenas felis diam, venenatis sed, interdum sed, dignissim nec, lacus. Curabitur ante tortor, condimentum sit amet, aliquam ut, porttitor vitae, purus. Nulla volutpat ante eget felis.




<div class="textmenu">
	<div class="header">
		That's fucktacular! But now I'd like to:
	</div>
	<div class="items">
		<a href="#"><div class="item"> + Download the source</div></a>
		<a href="#"><div class="item"> + Add a comment</div></a>
		<a href="#"><div class="item"> + Eat apples</div></a>
		<a href="#"><div class="item"> + Have sex with men</div></a>
		<a href="#"><div class="item"> + Report a bug in this</div></a>
	</div>		
</div>


</div>
<br />
<div class="title">
	Comments
</div>

<div class="text"> We could also just fuck this ...</div>