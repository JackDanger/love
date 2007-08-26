<?php
?>

<div class="title">
     Documentation
</div>
<div class="text" style="margin-bottom: 10px;">
	Some text right here.
</div>
<div class="textmenu">
	<div class="header">
		Documents
	</div>
	<div class="items">
		<a href="./docs"><div class="item"> + LÖVE Reference Manual 0.1-pre-pre-a</div></a>
		<a href="#"><div class="item"> + LÖVE Reference Manual 0.0.0.0.1</div></a>
	</div>		
</div>
<div class="text">

</div>
                            
<div class="title">
     Tutorials
</div>

<?php

for($i=0;$i<11;$i++)
{


?>

<div class="project">
     

  <div class="ss_box">
       <div class="top"><!-- --></div>
       <div class="image_info_inactive" onmouseover="ssOver(this)" onmouseout="ssOut(this)">
            <div class="title">Mega Game <?php echo $i; ?></div>
            <div class="date">2006-12-11 16:15:45</div> <br />
       </div>
       <img src="gfx/ss_particles.png" alt="Particles Screenshot" />
       <div class="caption">
            Particle system in full effect. Better check that
            multi-lines work and all that.
       </div>
       <div class="bot"><!-- --></div>
  </div>
  
     <div class="data">
          <div class="header">Tutorial <?php echo $i ?>: Mega Shit</div>
          <div class="author"> User Level: n00b </div>
          <div class="date"> Novermber 5th, 2007 </div>

     <div class="textmenu">
	<div class="items">
		<a href="#"><div class="item" style="border-color: #ddd;"> + Go To Tutorial</div></a>
		<a href="#"><div class="item" style="border-color: #ddd;"> + Download source</div></a>
	</div>
     </div>

     </div>


<div class="breaker"><!-- --></div>
</div>  <!-- Project -->

<?php } ?>
