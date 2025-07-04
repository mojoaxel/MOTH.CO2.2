import PlayCircleOutlineIcon from '@mui/icons-material/PlayCircleOutline';
import { Button } from '@mui/material';
import Accordion from '@mui/material/Accordion';
import AccordionDetails from '@mui/material/AccordionDetails';
import AccordionSummary from '@mui/material/AccordionSummary';
import Card from '@mui/material/Card';
import TextField from '@mui/material/TextField';
import { Stack } from '@mui/system';
import { KeyboardEvent, useEffect, useState } from 'react';
import ApiResponse from './ApiResponse';
import { IApiProperties } from '../types/IApiProperties';
import { IResponseProps } from '../types/IResponseProps';

/**
 * component, renders an input field
 * targets the 'dirout' endpoint
 * @param props
 * @returns
 */
const ApiDirOut = (props: IApiProperties) => {

  const apiName = 'dirout';
  const apiDesc = 'list the contents of a folder on the device';
  const apiType = 'json';

  const { boxUrl, panels, handlePanel, handleApiCall } = props;

  const [folder, setFolder] = useState<string>();
  const [responseProps, setResponseProps] = useState<IResponseProps>();

  const handleKeyUp = (e: KeyboardEvent<HTMLDivElement>) => {
    if (e.key === 'Enter') {
      issueApiCall();
    }
  }

  const issueApiCall = () => {
    handleApiCall({
      href: boxUrl,
      call: apiName,
      meth: 'GET',
      type: apiType,
      qstr: folder && folder !== "" ? { folder } : null
    });
  };

  /**
   * react hook (props[apiName])
   */
  useEffect(() => {

    console.debug(`⚙ updating ${apiName} component`, props[apiName]);
    if (props[apiName]) {

      let href = `${boxUrl}/${apiName}`;
      if (folder && folder !== "") {
        href += `?folder=${folder}`
      }

      setResponseProps({
        time: Date.now(),
        href,
        type: apiType,
        http: 'GET',
        data: props[apiName]
      });

    }

    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [props[apiName]]);

  const handleFolderChange = (event: React.ChangeEvent<HTMLInputElement>) => {
    setFolder(event.target.value);
  };

  return (
    <Accordion expanded={panels.indexOf(apiName) >= 0} onChange={(event, expanded) => handlePanel(apiName, expanded)}>
      <AccordionSummary>
        <div>
          <div id={apiName}>/{apiName}</div>
          <div style={{ fontSize: '0.75em' }}>{apiDesc}</div>
        </div>
      </AccordionSummary>
      <AccordionDetails>
        <Card>
          <Stack>
            <TextField
              label="folder"
              size='small'
              onChange={handleFolderChange}
              onKeyUp={handleKeyUp}
              helperText="optional folder name. specify to list the contents of a specific folder. leave empty to get the root folders contents"
            />
            <Button variant="contained" endIcon={<PlayCircleOutlineIcon />} onClick={issueApiCall}>
              click to execute
            </Button>
            {
              (responseProps) ? <ApiResponse {...responseProps} /> : null
            }
          </Stack>
        </Card>
      </AccordionDetails>
    </Accordion>
  );
}

export default ApiDirOut;