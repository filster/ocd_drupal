<?php
/**
 * @file
 * Template file for the theming example text form.
 *
 * Available custom variables:
 * - $text_form: A string containing the pre-rendered form.
 * - $text_form_content: An array of form elements keyed by the element name.
 *
 * The default example below renders the entire form and its form elements in
 * a default order provided by Drupal.
 *
 * Alternatively, you may print each form element in the order you desire,
 * adding any extra html markup you wish to decorate the form like this:
 *
 * <?php print $text_form_content['element_name']; ?>
 *
 * The following snippet will print the contents of the $text_form_content
 * array, hidden in the source of the page, for you to discover the individual
 * element names.
 *
 * <?php print '<!--' . print_r($text_form_content, TRUE) . '-->'; ?>
 */
?>
<!-- theming-example-text-form template -->
    <div class="gris2">
      <div class="container">
        <!-- Encabezado-->
        <div class="encabezado">
          <h1><?php print t('Usuaris'); ?> <strong>— <?php print t('Pacients'); ?></strong></h1>
        </div>
        <hr>
        <!-- Encabezado fin-->
      </div>
    </div>
    <div class="menuizqlayout gris2 recentlayout">
      <div class="container">
        <div class="content full centered">

	      	  <?php print $table_results; ?>

        </div>
      </div>
      <!-- Contenido fin-->
    </div>
