/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _EXAMPLE_FILE_NAME_H    /* Guard against multiple inclusion */
#define _EXAMPLE_FILE_NAME_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


  /* ************************************************************************** */
  /* ************************************************************************** */
  /* Section: Constants                                                         */
  /* ************************************************************************** */
  /* ************************************************************************** */

  /*  A brief description of a section can be given directly below the section
      banner.
   */


  /* ************************************************************************** */
  /** Descriptive Constant Name

    @Summary
      Brief one-line summary of the constant.
    
    @Description
      Full description, explaining the purpose and usage of the constant.
      <p>
      Additional description in consecutive paragraphs separated by HTML 
      paragraph breaks, as necessary.
      <p>
      Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
    
    @Remarks
      Any additional remarks
   */
#define KP 0.1
#define KI 0.05
#define KT 0.01
  
  
  
  void setDesiredValue(int value);
  int getDesiredValue();

 int PID(int param1, int param2);


  /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
